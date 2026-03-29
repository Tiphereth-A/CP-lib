#pragma once

#include "../../ds/bmat/lib.hpp"

namespace tifa_libs {

template <u32 MAXLEN>
CEXP bitmat<MAXLEN> trans_bmat(bitmat<MAXLEN> CR bmat) NE {
  const u32 R = bmat.row(), C = bmat.col();
  bitmat<MAXLEN> ret(C, R);
  flt_ (u32, r, 0, R)
    flt_ (u32, c, 0, C)
      if (bmat.test(r, c)) ret.set(c, r);
  return ret;
}

}  // namespace tifa_libs
