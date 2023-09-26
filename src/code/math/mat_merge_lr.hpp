#ifndef TIFA_LIBS_MATH_MAT_MERGE_LR
#define TIFA_LIBS_MATH_MAT_MERGE_LR

#include "../util/util.hpp"

namespace tifa_libs::math {

// [l] [r] -> [l r]
template <class Mat, class T = typename Mat::value_type>
inline Mat merge_lr(Mat const &l, Mat const &r) {
  size_t r_ = l.row();
  assert(r_ == r.row());
  size_t lc_ = l.col(), rc_ = r.col(), c_ = lc_ + rc_;
  Mat ret(r_, c_);
  ret.apply_range(0, r_, 0, lc_, [&l](size_t i, size_t j, T &val) { val = l(i, j); });
  ret.apply_range(0, r_, lc_, c_, [lc_, &r](size_t i, size_t j, T &val) { val = r(i, j - lc_); });
  return ret;
}

}  // namespace tifa_libs::math

#endif