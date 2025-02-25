#ifndef TIFALIBS_LALG_GE_BMAT
#define TIFALIBS_LALG_GE_BMAT

#include "bitmat.hpp"

namespace tifa_libs::math {

template <usz R, usz C>
CEXP u32 ge_bmat(bitmat<R, C> &bmat, bool clear_u = true) NE {
  CEXP usz rk_max = min(R, C);
  u32 rk = 0;
  for (u32 i = 0, c = 0; i < R; c = max(c, ++i)) {
    if (!bmat[i][c]) {
      u32 i2 = i;
      flt_ (u32, j, i + 1, R)
        if (bmat[j][c]) {
          i2 = j;
          break;
        }
      if (i2 != i) swap(bmat[i2], bmat[i]);
      else stable_sort(bmat.begin() + i, bmat.end(), [](auto CR l, auto CR r) NE { return l._Find_first() > r._Find_first(); });
      if (!bmat[i][c] && (c = (u32)bmat[i]._Find_next(c)) == C) break;
    }
    flt_ (u32, j, clear_u ? 0 : i + 1, R)
      if (j != i && bmat[j][c]) bmat[j] ^= bmat[i];
    if (++rk >= rk_max) break;
  }
  return rk;
}

}  // namespace tifa_libs::math

#endif