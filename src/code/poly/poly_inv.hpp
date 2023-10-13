#ifndef TIFALIBS_POLY_INV
#define TIFALIBS_POLY_INV

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_inv(poly<T> const &p, size_t n = 0) {
  assert(p[0] != 0);
  if (!n) n = p.size();
  poly<T> a{p[0].inv()};
  for (size_t i = 1; i < n; i *= 2) a = (a * 2 - (a * a * p).pre(i * 2)).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs::math

#endif