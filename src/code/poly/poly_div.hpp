#ifndef TIFALIBS_POLY_DIV
#define TIFALIBS_POLY_DIV

#include "poly_inv.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_div(poly<T> p, poly<T> q) {
  size_t n = p.size(), m = q.size();
  p.reverse();
  q.reverse();
  q.resize(n - m + 1);
  p.conv(poly_inv(q), n - m + 1);
  p.reverse();
  return p;
}

}  // namespace tifa_libs::math

#endif