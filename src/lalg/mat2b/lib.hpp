#pragma once

#include "../ds/bmat/lib.hpp"
#include "../ds/mat/lib.hpp"

namespace tifa_libs {

#define FOR1_(i, l, r) for (u32 i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_ (i, row_l, row_r)                       \
    FOR1_ (j, col_l, col_r)

template <u32 MAXLEN>
CEXP bitmat<MAXLEN> mat2b(matrix<bool> CR mat) NE {
  const u32 r = mat.row(), c = mat.col();
  bitmat<MAXLEN> ret(r, c);
  FOR2_ (i, 0, r, j, 0, c)
    if (mat(i, j)) ret._Unchecked_set((usz)i * c + j);
  return ret;
}

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs
