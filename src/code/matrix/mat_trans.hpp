#ifndef TIFALIBS_MATRIX_MAT_TRANS
#define TIFALIBS_MATRIX_MAT_TRANS

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class T = typename Mat::value_type>
Mat transpose(Mat const &mat) {
  u32 r_ = mat.row(), c_ = mat.col();
  Mat ret(c_, r_);
  ret.apply_range(0, c_, 0, r_, [&mat](u32 i, u32 j, T &val) { val = mat(j, i); });
  return ret;
}

}  // namespace tifa_libs::math

#endif