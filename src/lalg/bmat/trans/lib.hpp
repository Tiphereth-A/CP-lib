#pragma once

#include "../../ds/bmat/lib.hpp"

namespace tifa_libs::math {

template <usz R, usz C>
CEXP bitmat<C, R> trans_bmat(bitmat<R, C> CR bmat) NE {
  bitmat<C, R> ret;
  flt_ (usz, r, 0, R)
    flt_ (u32, c, 0, C) ret[c][r] = bmat[r][c];
  return ret;
}

}  // namespace tifa_libs::math
