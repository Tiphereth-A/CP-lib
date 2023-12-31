#ifndef TIFALIBS_CONV_CONV_NAIVE
#define TIFALIBS_CONV_CONV_NAIVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class U, class T = U>
requires(sizeof(U) <= sizeof(T))
constexpr vec<T> conv_naive(vec<U> const &l, vec<U> const &r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  u32 n = (u32)l.size(), m = (u32)r.size();
  vec<T> ans(ans_size);
  if (n < m)
    for (u32 j = 0; j < m; ++j)
      for (u32 i = 0; i < n; ++i) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  else
    for (u32 i = 0; i < n; ++i)
      for (u32 j = 0; j < m; ++j) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  return ans;
}

}  // namespace tifa_libs::math

#endif