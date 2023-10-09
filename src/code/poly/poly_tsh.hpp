#ifndef TIFALIBS_POLY_TSH
#define TIFALIBS_POLY_TSH

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_tsh(poly<T> const &f, T c, vec<u64> const &fact, vec<u64> const &ifact) {
  size_t n = f.size();
  poly<T> s = f, p(f.size());
  for (size_t i = 0; i < n; ++i) p[n - i - 1] = f[i] * fact[i];
  {
    T buf = 1;
    for (size_t i = 0; i < n; ++i, buf *= c) s[i] = buf * ifact[i];
  }
  (p *= s).resize(n);
  for (size_t i = 0; i < n; ++i) s[n - i - 1] = p[i] * ifact[n - i - 1];
  return s;
}

}  // namespace tifa_libs::math

#endif