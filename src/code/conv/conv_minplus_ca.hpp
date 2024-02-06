#ifndef TIFALIBS_CONV_CONV_MINPLUS_CA
#define TIFALIBS_CONV_CONV_MINPLUS_CA

#include "../opt/smawk.hpp"

namespace tifa_libs::math {

//! assume a is convex, aka. $a_{i-1} - a_{i-2} \leq a_i - a_{i-1}$
//! assume b is arbitary, aka. $b_i = b_j \iff i = j$
template <class T>
constexpr vec<T> conv_minplus_ca(vec<T> const& a, vec<T> const& b) {
  u32 n = (u32)a.size(), m = (u32)b.size();
  vec<u32> argmin = smawk(
      n + m - 1, m,
      [&](u32 k, u32 j1, u32 j2) -> bool {
        u32 i1 = k - j1, i2 = k - j2;
        if (i2 < 0) return 1;
        if (i1 >= n) return 0;
        return a[i1] + b[j1] < a[i2] + b[j2];
      });
  vec<T> c(n + m - 1);
  for (u32 k = 0; k < n + m - 1; ++k) {
    u32 j = argmin[k];
    c[k] = a[k - j] + b[j];
  }
  return c;
}

}  // namespace tifa_libs::math

#endif