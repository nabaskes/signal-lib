/* @author: nabaskes

performs discrete wavelet transform on the given
*/

#include <vector>
#include <math.h>
#include <iostream>
#include <tuple>

void dwt (std::vector<double>* arr) {
  int num_els = arr->size();
  int n = (int) log2(num_els); // num_els must be power of 2


  for (int i=0; i<n; i++) {
    std::vector<double> temp_diffs;
    int num_steps = num_els / (2 * pow(2, i));
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

void idwt(std::vector<double>* arr) {
  int num_els = arr->size();
  int n = (int) log2(num_els);

  for(int i=0; i<n; i++) {
    std::vector<std::tuple<double, double>> pairs;
    int num_steps = num_els / (pow(2, n - i));
    pairs.reserve(num_steps);
    std::cout << "numsteps" <<  num_steps << "\n";

    for(int k=0; k<num_steps; k++) {
      double first = (*arr)[k] + (*arr)[k + num_steps];
      double second = (*arr)[k] - (*arr)[k + num_steps];
      pairs.push_back(std::make_tuple(first, second));
    }


    for(int k=0; k<num_steps; k++) {
      (*arr)[2*k] = std::get<0>(pairs[k]);
      (*arr)[2*k+1] = std::get<1>(pairs[k]);
    }
  }

  return;
}

void dwt_2d(std::vector<std::vector<double>>* arr) {
  int rows = arr->size();
  int cols = (*arr)[0].size();
  std::vector<double> T;
  T.reserve(rows);

  // first transform each row
  for(int i=0; i<rows; i++) {
    dwt(&((*arr)[i]));
  }

  for(int j=0; j<cols; j++) {
    for(int i=0; i<rows; i++){
      T[i] = (*arr)[i][j];
    }

    dwt(&T);

    for(int i=0; i<rows; i++) {
      (*arr)[i][j] = T[i];
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
  idwt(&arr);

  for(auto i: arr) {
    std::cout << (i) << "\n";
  }

  std::cout << "\n";

  std::vector<double> arr2 {3,1,0,4,8,6,9,9};
  dwt(&arr2);

  for (auto i: arr2) {
    std::cout << (i) << "\n";
  }

  std::cout << "\n";

  idwt(&arr2);

  for(auto i: arr2) {
    std::cout << (i) << "\n";
  }
}
