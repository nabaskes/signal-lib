#include <vector>
#include <stdio.h>
#include "filter.cpp"

int main() {
  std::vector<double> x, b, a;
  x.reserve(100);
  for(int i=0; i<100; i++) {
    x.push_back(i);
  }

  b.reserve(1);
  a.reserve(1);
  b.push_back(1);
  b.push_back(2);
  a.push_back(1);
  a.push_back(5);

  std::vector <double> y = simple_filter(b, a, x);



  std::vector<double>::iterator it;
  for(it=y.begin(); it != y.end(); it++) {
    printf("%f\n", *it);
  }


  return 0;
}
