#ifndef TIFA_LIBS_MATH_MAT_GE_SWAPR_
#define TIFA_LIBS_MATH_MAT_GE_SWAPR_

#include "../util/util.hpp"

namespace tifa_libs::math::ge_detail__ {

template <class Mat>
constexpr bool swapr__(Mat &mat, size_t &r_, size_t r_pre_, size_t r_end) {
  r_ = r_pre_;
  for (size_t j = r_ + 1; j < r_end; ++j)
    if (mat.data()[r_] < mat.data()[j]) r_ = j;
  if (r_ != r_pre_) {
    mat.swap_row(r_, r_pre_);
    return true;
  }
  return false;
}

}  // namespace tifa_libs::math::ge_detail__

#endif