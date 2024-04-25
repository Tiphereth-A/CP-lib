#ifndef TIFALIBS_CONV_CONV_NAIVE
#define TIFALIBS_CONV_CONV_NAIVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class U, class T = U>
requires(sizeof(U) <= sizeof(T))
CEXP vec<T> conv_naive(vec<U> CR l, vec<U> CR r, u32 ans_size = 0) {
  if (l.empty() || r.empty()) return {};
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  u32 n = (u32)l.size(), m = (u32)r.size();
  vec<T> ans(ans_size);
  if (n < m)
    flt_ (u32, j, 0, m)
      flt_ (u32, i, 0, n) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  else
    flt_ (u32, i, 0, n)
      flt_ (u32, j, 0, m) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  return ans;
}

}  // namespace tifa_libs::math

#endif