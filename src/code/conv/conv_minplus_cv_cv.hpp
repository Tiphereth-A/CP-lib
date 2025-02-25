#ifndef TIFALIBS_CONV_CONV_MINPLUS_CV_CV
#define TIFALIBS_CONV_CONV_MINPLUS_CV_CV

#include "../util/util.hpp"

namespace tifa_libs::math {

//! assume a and b are convex, aka. $a_{i-1} - a_{i-2} \leq a_i - a_{i-1}$ and it also holds for b
template <class T>
CEXP vec<T> conv_minplus_cv_cv(vec<T> CR a, vec<T> CR b) NE {
  const u32 n = (u32)a.size(), m = (u32)b.size();
  vec<T> c(n + m - 1);
  c[0] = a[0] + b[0];
  flt_ (u32, k, 0, n + m - 2, i = 0)
    if (const u32 j = k - i; j == m - 1 || (i < n - 1 && a[i + 1] + b[j] < a[i] + b[j + 1])) c[k + 1] = a[++i] + b[j];
    else c[k + 1] = a[i] + b[j + 1];
  return c;
}

}  // namespace tifa_libs::math

#endif