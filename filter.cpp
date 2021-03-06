/* @author: nabaskes

   cpp implementation of filter function from matlab

   I modelled this off code from the octave signal library

 */

#include <vector>
#include <iterator>
#include <stdio.h>



std::vector< double > filtic(std::vector<double> b,
			     std::vector<double> a,
			     std::vector<double> y,
			     std::vector<double> x) {

  int nz = (b.size() > a.size()) ? b.size() - 1 : a.size() - 1;

  // pad lengths of a, b, x, and y, if necessary, otherwise, don't
  int lena = a.size();
  a.reserve(nz);
  for (int i=lena; i<nz; i++) {
    a[i] = 0;
  }

  int lenb = b.size();
  b.reserve(nz);
  for (int i=lenb; i<nz; i++) {
    b[i] = 0;
  }

  int leny = y.size();
  y.reserve(nz);
  for (int i=leny; i<nz; i++) {
    y[i] = 0;
  }

  int lenx = x.size();
  x.reserve(nz);
  for (int i=lenx; i<nz; i++) {
    x[i] = 0;
  }

  std::vector<double> zf;
  zf.reserve(nz);

  for (int i=nz-1; i > 0; i--) {
    for (int j=i; j<nz-1; j++) {
      zf[j-1] = b[j]*x[i-1] - a[j] * y[i-1] + zf[j];
    }
    zf[nz-1] = b[nz] * x[i-1] - a[nz] * y[i-1];
  }

  return zf;
}

std::vector <double> filter(std::vector<double> b,
			    std::vector<double> a,
			    std::vector<double> x) {

  size_t nz = (b.size() > a.size()) ? b.size() - 1 : a.size() - 1;
  printf("nz: %d as b: %d and a: %d\n", nz, b.size(), a.size());
  std::vector <double> y;
  y.reserve(x.size());

  // if necessary, pad lengths of a, b and x
  size_t lena = a.size();
  for (size_t i=lena; i<nz; i++) {
    a[i] = 0;
  }

  size_t lenb = b.size();
  for (size_t i=lenb; i<nz; i++) {
    b[i] = 0;
  }

  size_t lenx = x.size();
  for (size_t i=lenx; i<nz; i++) {
    x[i] = 0;
  }


  // renormalize a and b to a[1]
  if( a[0] != 1) {
    for (size_t i=0; i < a.size(); i++) {
      a[i] = a[i] / a[1];
    }

    for (size_t i=0; i< b.size(); i++) {
      b[i] = b[i] / a[1];
    }

    a[1] = 1;
  }


  int bsum, asum;

  for (int n=0; n < x.size(); n++) {
    asum = 0;
    bsum = 0;

    for (int k = 1; k < a.size() - 1; k++) {
      if ((n - k) < 0) {
	continue;
      }
      asum += a[k+1] * y[n - k];
    }

    for (int k = 0; k < b.size() - 1; k++) {
      if ((n - k) < 0) {
	continue;
      }
      bsum += b[k+1] * x[n - k];
    }

    y.push_back(bsum - asum);
  }

  return y;
}


std::vector <double> simple_filter(std::vector <double> b,
				   std::vector <double> a,
				   std::vector <double> x) {
  int nb = b.size();
  int na = a.size();
  int nz = (nb > na) ? nb : na;

  std::vector<double> y;
  y.reserve(x.size());

  for (int k = 0; k < x.size(); k++) {
    y.push_back(0);

    for(int kb = 0; kb < b.size(); kb++) {
      if ( (k - kb) >= 0) {
	y[k] += b[kb] * x[k - kb];
      }
    }

    for(int ka = 1; ka < a.size(); ka++) {
      if ( (k - ka) >= 0) {
	y[k] += a[ka] * y[k - ka];
      }
    }

  }

  return y;
}
