#pragma once

#include "../../ds/bmat/lib.hpp"

namespace tifa_libs {

template <u32 MAXLEN>
CEXP bitmat<MAXLEN> mul_bmat(bitmat<MAXLEN> CR l, bitmat<MAXLEN> CR trans_r) NE {
  const u32 I = l.row(), J = l.col(), K = trans_r.row();
  assert(trans_r.col() == J);
  bitmat<MAXLEN> ret(I, K);
  auto row_find_next_l = [&](u32 i, u32 from) -> u32 {
    const usz base = (usz)i * J;
    usz p;
    if (!from) p = base ? l._Find_next(base - 1) : l._Find_first();
    else p = l._Find_next(base + from - 1);
    return p < (usz)(i + 1) * J ? (u32)(p - base) : J;
  };
  flt_ (u32, i, 0, I)
    flt_ (u32, k, 0, K) {
      bool v = false;
      for (u32 j = row_find_next_l(i, 0); j < J; j = row_find_next_l(i, j + 1)) v ^= trans_r._Unchecked_test((usz)k * J + j);
      if (v) ret._Unchecked_set((usz)i * K + k);
    }
  return ret;
}

}  // namespace tifa_libs
