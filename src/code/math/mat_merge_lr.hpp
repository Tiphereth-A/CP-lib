#ifndef TIFA_LIBS_MATH_MAT_MERGE_LR
#define TIFA_LIBS_MATH_MAT_MERGE_LR

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

// [l] [r] -> [l r]
template <class T>
inline matrix<T> merge_lr(matrix<T> const &l, matrix<T> const &r) {
  size_t r_ = l.row();
  assert(r_ == r.row());
  size_t lc_ = l.col(), rc_ = r.col(), c_ = lc_ + rc_;
  matrix<T> ret(r_, c_);
  ret.apply(0, r_, 0, lc_, [&l](size_t i, size_t j, T &val) { val = l(i, j); });
  ret.apply(0, r_, lc_, c_, [lc_, &r](size_t i, size_t j, T &val) { val = r(i, j - lc_); });
  return ret;
}

}  // namespace tifa_libs::math

#endif