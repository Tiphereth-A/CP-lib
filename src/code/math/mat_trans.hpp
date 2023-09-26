#ifndef TIFA_LIBS_MATH_MAT_TRANS
#define TIFA_LIBS_MATH_MAT_TRANS

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class T = typename Mat::value_type>
inline Mat transpose(Mat const &mat) {
  size_t r_ = mat.row(), c_ = mat.col();
  Mat ret(c_, r_);
  ret.apply(0, c_, 0, r_, [&mat](size_t i, size_t j, T &val) { val = mat(j, i); });
  return ret;
}

}  // namespace tifa_libs::math

#endif