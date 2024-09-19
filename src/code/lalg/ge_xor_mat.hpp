#ifndef TIFALIBS_LALG_GE_XOR_MAT
#define TIFALIBS_LALG_GE_XOR_MAT

#include "ge_swapr_mat_.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0>
requires std::same_as<TPN Mat::val_t, bool>
CEXP i32 ge_xor(Mat &mat, Is0, bool clear_u = true) {
  const u32 r_ = mat.row(), c_ = mat.col(), rk_max = min(r_, c_);
  u32 rk = 0;
  bool neg = false;
  for (u32 i = 0, now_row = 0, j_ = i; i < mat.row(); ++i) {
    if (j_ = max(j_, i); !mat(rk, i)) {
      neg ^= ge_impl_::swapr__(mat, now_row, rk, mat.row());
      while (j_ < c_ && !mat(rk, j_)) ++j_;
      if (j_ == c_) break;
    }
    for (u32 j = clear_u ? 0 : rk + 1; j < mat.row(); ++j) {
      if (j == rk || !mat(j, j_)) continue;
      mat(j, j_) = false;
      flt_ (u32, k, j_ + 1, c_)
        if (mat(rk, k)) mat(j, k) = !mat(j, k);
    }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i32)rk) : (i32)rk;
}

}  // namespace tifa_libs::math

#endif