#ifndef TIFALIBS_LALG_MAT_POW
#define TIFALIBS_LALG_MAT_POW

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat>
constexpr Mat pow(Mat mat, u64 b) {
  u32 n = mat.row();
  assert(n == mat.col());
  Mat res(n, n);
  for (u32 i = 0; i < n; ++i) res(i, i) = 1;
  for (; b; b >>= 1, mat *= mat)
    if (b & 1) res *= mat;
  return res;
}

}  // namespace tifa_libs::math

#endif