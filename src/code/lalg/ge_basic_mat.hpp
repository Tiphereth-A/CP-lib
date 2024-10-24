#ifndef TIFALIBS_LALG_GE_BASIC_MAT
#define TIFALIBS_LALG_GE_BASIC_MAT

#include "ge_swapr_mat_.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0>
requires requires(Is0 is0, TPN Mat::val_t t) {
  { is0(t) } -> std::same_as<bool>;
}
CEXP i32 ge_basic(Mat& mat, Is0&& is0, bool clear_u = true) {
  using T = TPN Mat::val_t;
  const u32 r_ = mat.row(), c_ = mat.col(), rk_max = min(r_, c_);
  u32 rk = 0;
  bool neg = false;
  for (u32 i = 0, now_r = 0, j_ = i; i < mat.row(); ++i) {
    neg ^= ge_impl_::swapr__(mat, now_r, rk, mat.row()), j_ = max(j_, i);
    while (j_ < c_ && is0(mat(rk, j_))) ++j_;
    if (j_ == c_) break;
    for (u32 j = clear_u ? 0 : rk + 1; j < mat.row(); ++j) {
      if (j == rk || is0(mat(j, j_))) continue;
      T _ = mat(j, j_) / mat(rk, j_);
      mat(j, j_) = 0;
      for (u32 k = j_ + 1; k < c_; ++k) mat(j, k) -= mat(rk, k) * _;
    }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i32)rk) : (i32)rk;
}

}  // namespace tifa_libs::math

#endif