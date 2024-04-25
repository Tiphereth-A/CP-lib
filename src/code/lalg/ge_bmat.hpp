#ifndef TIFALIBS_LALG_GE_BMAT
#define TIFALIBS_LALG_GE_BMAT

#include "bitmat.hpp"

namespace tifa_libs::math {

template <usz R, usz C>
CEXP u32 ge_bmat(bitmat<R, C> &bmat, bool clear_u = true) {
  CEXP usz rk_max = min(R, C);
  u32 rk = 0;
  for (u32 i = 0, now_row = 0, j_ = i; i < R; ++i) {
    j_ = max(j_, i);
    if (!bmat[rk][i]) {
      now_row = rk;
      for (u32 j = now_row + 1; j < R; ++j)
        if (bmat[j][i]) now_row = j;
      if (now_row != rk) swap(bmat[now_row], bmat[rk]);
      while (j_ < C && !bmat[rk][j_]) ++j_;
      if (j_ == C) break;
    }
    for (u32 j = clear_u ? 0 : rk + 1; j < R; ++j) {
      if (j == rk || !bmat[j][j_]) continue;
      bmat[j] ^= bmat[rk];
    }
    if (++rk >= rk_max) break;
  }
  return rk;
}

}  // namespace tifa_libs::math

#endif