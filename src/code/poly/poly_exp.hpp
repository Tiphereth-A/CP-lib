#ifndef TIFALIBS_POLY_EXP
#define TIFALIBS_POLY_EXP

#include "poly_ln.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_exp(poly<T> const &p, size_t n = 0) {
  assert(p[0] == 0);
  if (!n) n = p.size();
  poly<T> _ = p + 1, a{1};
  for (size_t i = 1; i < n; i *= 2) a = (a * (_.pre(i * 2) - poly_ln(a, i * 2))).pre(i * 2);
  return a.pre(n);
}

}  // namespace tifa_libs::math

#endif