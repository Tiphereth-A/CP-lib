#ifndef TIFALIBS_LALG_POW_MAT
#define TIFALIBS_LALG_POW_MAT

#include "../math/qpow.hpp"

namespace tifa_libs::math {

template <class Mat>
CEXP Mat pow(Mat CR mat, u64 b) NE {
  const u32 n = mat.row();
  assert(n == mat.col());
  Mat id(n, n);
  flt_ (u32, i, 0, n) id(i, i) = 1;
  return qpow(mat, b, id);
}

}  // namespace tifa_libs::math

#endif