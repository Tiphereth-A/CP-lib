#ifndef TIFALIBS_LALG_POW_MAT
#define TIFALIBS_LALG_POW_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat>
CEXP Mat pow(Mat mat, u64 b) {
  const u32 n = mat.row();
  assert(n == mat.col());
  Mat res(n, n);
  flt_ (u32, i, 0, n) res(i, i) = 1;
  for (; b; b /= 2, mat *= mat)
    if (b & 1) res *= mat;
  return res;
}

}  // namespace tifa_libs::math

#endif