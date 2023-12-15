#ifndef TIFALIBS_LALG_MAT_MERGE_UD
#define TIFALIBS_LALG_MAT_MERGE_UD

#include "mat.hpp"

namespace tifa_libs::math {

// [u] [d] -> [u; d]
template <class T>
constexpr matrix<T> mat_merge_ud(const matrix<T> &u, const matrix<T> &d) {
  u32 c_ = u.col();
  assert(c_ == d.col());
  u32 ur_ = u.row(), dr_ = d.row(), r_ = ur_ + dr_;
  matrix<T> ret(r_, c_);
  ret.apply_range(0, ur_, 0, c_, [&u](u32 i, u32 j, T &val) { val = u(i, j); });
  ret.apply_range(ur_, r_, 0, c_, [ur_, &d](u32 i, u32 j, T &val) { val = d(i - ur_, j); });
  return ret;
}

}  // namespace tifa_libs::math

#endif