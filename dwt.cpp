/* @author: nabaskes

performs discrete wavelet transform on the given
*/

#include <vector>
#include <math.h>
#include <iostream>

void dwt (std::vector<double>* arr) {
  int num_els = arr->size();
  int n = (int) log2(num_els); // num_els must be power of 2


  for (int i=0; i<n; i++) {
    std::vector<double> temp_diffs;
    int num_steps = num_els / (2 * pow(2, i));
    std::cout << "numsteps: " << num_steps << "\n";
    temp_diffs.reserve(num_steps);

    for (int k=0; k<num_steps; k++) {
      temp_diffs.push_back( ( (*arr)[2*k] - (*arr)[2*k+1])/2);
      (*arr)[k] = ( (*arr)[2*k] + (*arr)[2*k+1]) / 2;
    }

    for (int k=num_steps; k<2*num_steps; k++) {
      (*arr)[k] = temp_diffs[k - num_steps];
    }

  }
  return;
}

int main(){
  std::vector<double> arr {5.0, 1.0, 2.0, 8.0};
  dwt(&arr);

  for (auto i: arr) {
    std::cout << (i) << "\n";
  }

  std::cout << "\n";

  std::vector<double> arr2 {3,1,0,4,8,6,9,9};
  dwt(&arr2);

  for (auto i: arr2) {
    std::cout << (i) << "\n";
  }
}