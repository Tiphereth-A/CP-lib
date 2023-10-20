#ifndef TIFALIBS_CONV_WHT
#define TIFALIBS_CONV_WHT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
void wht(vec<T>& f) {
  size_t n = f.size();
  for (size_t i = 1; i < n; i *= 2)
    for (size_t j = 0; j < n; ++j)
      if (!(j & i)) {
        T x = f[j], y = f[j | i];
        f[j] = x + y;
        f[j | i] = x - y;
      }
}

template <class T>
void iwht(vec<T>& f) {
  size_t n = f.size();
  wht(f);
  if constexpr (std::is_integral_v<T>)
    for (auto& x : f) x /= n;
  else {
    T _ = T(1) / T(n);
    for (auto& x : f) x *= _;
  }
}

}  // namespace tifa_libs::math

#endif