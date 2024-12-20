#ifndef TIFALIBS_LALG_TRANS_MAT
#define TIFALIBS_LALG_TRANS_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat>
CEXP Mat transpose(Mat CR mat) {
  const u32 r_ = mat.row(), c_ = mat.col();
  Mat ret(c_, r_);
  return ret.apply_range(0, c_, 0, r_, [&mat](u32 i, u32 j, auto &val) { val = mat(j, i); }), ret;
}

}  // namespace tifa_libs::math

#endif