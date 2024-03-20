#ifndef TIFALIBS_LALG_BITMAT_GE
#define TIFALIBS_LALG_BITMAT_GE

#include "bitmat.hpp"

namespace tifa_libs::math {

template <usz R, usz C>
constexpr u32 bitmat_ge(bitmat<R, C> &bmat, bool clear_u = true) {
  constexpr usz rk_max = std::min(R, C);
  u32 rk = 0;
  for (u32 i = 0, now_row = 0, j_ = i; i < R; ++i) {
    j_ = std::max(j_, i);
    if (!bmat[rk][i]) {
      now_row = rk;
      for (u32 j = now_row + 1; j < R; ++j)
        if (bmat[j][i]) now_row = j;
      if (now_row != rk) std::swap(bmat[now_row], bmat[rk]);
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