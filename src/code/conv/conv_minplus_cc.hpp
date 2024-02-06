#ifndef TIFALIBS_CONV_CONV_MINPLUS_CC
#define TIFALIBS_CONV_CONV_MINPLUS_CC

#include "../util/util.hpp"

namespace tifa_libs::math {

//! assume a and b are convex, aka. $a_{i-1} - a_{i-2} \leq a_i - a_{i-1}$ and it also holds for b
template <class T>
constexpr vec<T> conv_minplus_cc(vec<T> const& a, vec<T> const& b) {
  u32 n = (u32)a.size(), m = (u32)b.size();
  vec<T> c(n + m - 1);
  c[0] = a[0] + b[0];
  for (u32 k = 0, i = 0; k < n + m - 2; ++k) {
    u32 j = k - i;
    if (j == m - 1 || (i < n - 1 && a[i + 1] + b[j] < a[i] + b[j + 1])) c[k + 1] = a[++i] + b[j];
    else c[k + 1] = a[i] + b[++j];
  }
  return c;
}

}  // namespace tifa_libs::math

#endif