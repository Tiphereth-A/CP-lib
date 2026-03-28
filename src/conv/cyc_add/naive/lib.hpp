#pragma once

#include "../../../util/alias/others/lib.hpp"

namespace tifa_libs {

template <class U, class T = U>
requires(sizeof(U) <= sizeof(T))
CEXP vec<T> convcyc_naive(vec<U> CR l, vec<U> CR r) NE {
  retif_((l.empty() || r.empty()) [[unlikely]], {});
  assert(l.size() == r.size());
  const u32 n = (u32)l.size();
  vec<T> ans(n);
  flt_ (u32, i, 0, n) {
    flt_ (u32, j, 0, n - i) ans[i + j] += (T)l[i] * (T)r[j];
    flt_ (u32, j, n - i, n) ans[i + j - n] += (T)l[i] * (T)r[j];
  }
  return ans;
}

}  // namespace tifa_libs
