#ifndef TIFALIBS_CONV_CONVCYC_NAIVE
#define TIFALIBS_CONV_CONVCYC_NAIVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class U, class T = U>
requires(sizeof(U) <= sizeof(T))
CEXP vec<T> convcyc_naive(vec<U> CR l, vec<U> CR r) NE {
  if (l.empty() || r.empty()) return {};
  assert(l.size() == r.size());
  const u32 n = (u32)l.size();
  vec<T> ans(n);
  flt_ (u32, i, 0, n) {
    flt_ (u32, j, 0, n - i) ans[i + j] += (T)l[i] * (T)r[j];
    flt_ (u32, j, n - i, n) ans[i + j - n] += (T)l[i] * (T)r[j];
  }
  return ans;
}

}  // namespace tifa_libs::math

#endif