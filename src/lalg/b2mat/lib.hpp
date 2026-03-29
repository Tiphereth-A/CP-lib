#pragma once

#include "../ds/bmat/lib.hpp"
#include "../ds/mat/lib.hpp"

namespace tifa_libs {

template <u32 MAXLEN>
CEXP matrix<bool> b2mat(bitmat<MAXLEN> CR bmat) NE {
  const u32 R = bmat.row(), C = bmat.col();
  matrix<bool> ret(R, C);
  ret.apply([&bmat, C](u32 i, u32 j, auto& b) NE { b = bmat._Unchecked_test((usz)i * C + j); });
  return ret;
}

}  // namespace tifa_libs
