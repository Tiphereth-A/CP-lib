#pragma once

#include "../../ds/bmat/lib.hpp"

namespace tifa_libs {

template <u32 MAXLEN>
CEXP u32 ge_bmat(bitmat<MAXLEN>& bmat, bool clear_u = true) NE {
  const u32 R = bmat.row(), C = bmat.col();
  const u32 rk_max = min(R, C);
  u32 rk = 0;
  auto row_find_next = [&](u32 i, u32 from) -> u32 {
    const usz base = (usz)i * C;
    usz p;
    if (!from) p = base ? bmat._Find_next(base - 1) : bmat._Find_first();
    else p = bmat._Find_next(base + from - 1);
    return p < (usz)(i + 1) * C ? (u32)(p - base) : C;
  };
  auto row_swap = [&](u32 a, u32 b) {
    if (a == b) return;
    flt_ (u32, j, 0, C) {
      bool ta = bmat.test(a, j), tb = bmat.test(b, j);
      if (tb) bmat._Unchecked_set((usz)a * C + j);
      else bmat._Unchecked_reset((usz)a * C + j);
      if (ta) bmat._Unchecked_set((usz)b * C + j);
      else bmat._Unchecked_reset((usz)b * C + j);
    }
  };
  auto row_xor = [&](u32 dst, u32 src) {
    for (u32 j = row_find_next(src, 0); j < C; j = row_find_next(src, j + 1)) bmat._Unchecked_flip((usz)dst * C + j);
  };
  for (u32 i = 0, c = 0; i < R; c = max(c, ++i)) {
    if (!bmat.test(i, c)) {
      u32 i2 = i;
      flt_ (u32, j, i + 1, R)
        if (bmat.test(j, c)) {
          i2 = j;
          break;
        }
      if (i2 != i) row_swap(i2, i);
      else {
        u32 best = i;
        u32 best_pos = row_find_next(i, 0);
        flt_ (u32, j, i + 1, R) {
          u32 p = row_find_next(j, 0);
          if (p < best_pos) best = j, best_pos = p;
        }
        row_swap(i, best);
      }
      if (!bmat.test(i, c) && (c = row_find_next(i, c + 1)) == C) break;
    }
    flt_ (u32, j, clear_u ? 0 : i + 1, R)
      if (j != i && bmat.test(j, c)) row_xor(j, i);
    if (++rk >= rk_max) break;
  }
  return rk;
}

}  // namespace tifa_libs
