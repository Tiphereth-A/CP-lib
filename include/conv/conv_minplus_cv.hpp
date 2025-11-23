#ifndef TIFALIBS_CONV_CONV_MINPLUS_CV
#define TIFALIBS_CONV_CONV_MINPLUS_CV

#include "../opt/smawk.hpp"

namespace tifa_libs::math {

//! assume a is convex, aka. $a_{i-1} - a_{i-2} \leq a_i - a_{i-1}$
//! assume b is arbitrary, aka. $b_i = b_j \iff i = j$
template <class T>
CEXP vec<T> conv_minplus_cv(vec<T> CR a, vec<T> CR b) NE {
  const u32 n = (u32)a.size(), m = (u32)b.size();
  const vecu argmin = opt::smawk(
      n + m - 1,
      m,
      [&](u32 k, u32 j1, u32 j2) NE -> bool {
        i32 i1 = (i32)k - (i32)j1, i2 = (i32)k - (i32)j2;
        if (i2 < 0) return 1;
        if (i1 >= (i32)n) return 0;
        return a[(u32)i1] + b[j1] < a[(u32)i2] + b[j2];
      });
  vec<T> c(n + m - 1);
  flt_ (u32, k, 0, n + m - 1) c[k] = a[k - argmin[k]] + b[argmin[k]];
  return c;
}

}  // namespace tifa_libs::math

#endif