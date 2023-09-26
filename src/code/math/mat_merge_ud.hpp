#ifndef TIFA_LIBS_MATH_MAT_MERGE_UD
#define TIFA_LIBS_MATH_MAT_MERGE_UD

#include "../util/util.hpp"

namespace tifa_libs::math {

// [u] [d] -> [u; d]
template <class Mat, class T = typename Mat::value_type>
inline Mat merge_ud(const Mat &u, const Mat &d) {
  size_t c_ = u.col();
  assert(c_ == d.col());
  size_t ur_ = u.row(), dr_ = d.row(), r_ = ur_ + dr_;
  Mat ret(r_, c_);
  ret.apply_range(0, ur_, 0, c_, [&u](size_t i, size_t j, T &val) { val = u(i, j); });
  ret.apply_range(ur_, r_, 0, c_, [ur_, &d](size_t i, size_t j, T &val) { val = d(i - ur_, j); });
  return ret;
}

}  // namespace tifa_libs::math

#endif