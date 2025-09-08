#ifndef TIFALIBS_CONV_CONV_NAIVE
#define TIFALIBS_CONV_CONV_NAIVE

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

CEXP inline u32 CONV_NAIVE_THRESHOLD = 16;
template <class U, class T = U>
requires(sizeof(U) <= sizeof(T))
CEXP vec<T> conv_naive(vec<U> CR l, vec<U> CR r, u32 ans_size = 0) NE {
  retif_((l.empty() || r.empty()) [[unlikely]], {});
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  vec<T> ans(ans_size);
  u32 n = (u32)l.size(), m = (u32)r.size();
  auto &&l_ = n < m ? r : l, &&r_ = n < m ? l : r;
  if (n < m) swap(n, m);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, min(m, ans_size - i)) ans[i + j] += (T)l_[i] * (T)r_[j];
  return ans;
}

}  // namespace tifa_libs::math

#endif