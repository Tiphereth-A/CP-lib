#ifndef TIFALIBS_LALG_TR_MAT
#define TIFALIBS_LALG_TR_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat>
CEXP auto trace(Mat CR mat) {
  u32 n = mat.row();
  assert(n == mat.col());
  TPN Mat::value_type ret{};
  flt_ (u32, i, 0, n) ret += mat(i, i);
  return ret;
}

}  // namespace tifa_libs::math

#endif