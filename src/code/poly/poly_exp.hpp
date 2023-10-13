#ifndef TIFALIBS_POLY_EXP
#define TIFALIBS_POLY_EXP

#include "poly_ln.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_exp(poly<T> const &p, size_t n = 0) {
  assert(p[0] == 0);
  if (!n) n = p.size();
  poly<T> _ = p, a{1};
  ++_[0];
  for (size_t i = 1; i < n; i *= 2) a = (a * (poly<T>(_).do_resize(i * 2) - poly_ln(p, i * 2))).do_resize(i * 2);
  return a.do_resize(n);
}

}  // namespace tifa_libs::math

#endif