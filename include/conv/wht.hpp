#ifndef TIFALIBS_CONV_WHT
#define TIFALIBS_CONV_WHT

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

template <class T>
CEXP void wht(vec<T>& f, u32 n = 0) NE {
  if (!n) n = (u32)f.size();
  for (u32 i = 1; i < n; i *= 2)
    flt_ (u32, j, 0, n)
      if (!(j & i)) {
        const T x = f[j], y = f[j | i];
        f[j] = x + y, f[j | i] = x - y;
      }
}
template <class T>
CEXP void iwht(vec<T>& f, u32 n = 0) NE {
  if (!n) n = (u32)f.size();
  if CEXP (wht(f, n); std::is_integral_v<T>)
    for (auto& x : f) x /= n;
  else
    for (const T _ = T(1) / T(n); auto& x : f) x *= _;
}

}  // namespace tifa_libs::math

#endif