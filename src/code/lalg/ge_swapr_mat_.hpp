#ifndef TIFALIBS_LALG_GE_SWAPR_MAT_
#define TIFALIBS_LALG_GE_SWAPR_MAT_

#include "../util/util.hpp"

namespace tifa_libs::math::ge_impl_ {

template <class Mat>
CEXP bool swapr__(Mat &mat, u32 &r_, u32 r_pre_, u32 r_end) {
  for (u32 j = (r_ = r_pre_) + 1; j < r_end; ++j)
    if (mat.data()[r_] < mat.data()[j]) r_ = j;
  if (r_ != r_pre_) return mat.swap_row(r_, r_pre_), true;
  return false;
}

}  // namespace tifa_libs::math::ge_impl_

#endif