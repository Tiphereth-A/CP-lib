#ifndef TIFALIBS_LALG_TRANS_MAT
#define TIFALIBS_LALG_TRANS_MAT

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

template <class Mat>
CEXP Mat transpose(Mat CR mat) NE {
  const u32 r_ = mat.row(), c_ = mat.col();
  Mat ret(c_, r_);
  ret.apply_range(0, c_, 0, r_, [&mat](u32 i, u32 j, auto& val) NE { val = mat(j, i); });
  return ret;
}

}  // namespace tifa_libs::math

#endif