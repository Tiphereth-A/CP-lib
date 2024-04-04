#ifndef TIFALIBS_LALG_GE_EUCLID_MAT
#define TIFALIBS_LALG_GE_EUCLID_MAT

#include "ge_swapr_mat_.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0, class Div>
requires requires(Is0 is0, Div div, typename Mat::value_type t) {
  { is0(t) } -> std::same_as<bool>;
  { div(t, t) } -> std::same_as<typename Mat::value_type>;
}
constexpr i32 ge_euclid(Mat& mat, Is0&& is0, Div&& div, bool clear_u = true) {
  using T = typename Mat::value_type;
  u32 r_ = mat.row(), c_ = mat.col(), rk_max = std::min(r_, c_);
  u32 rk = 0;
  bool neg = false;
  for (u32 i = 0, now_row = 0, j_ = i; i < mat.row(); ++i) {
    neg ^= ge_impl_::swapr__(mat, now_row, rk, mat.row());
    j_ = std::max(j_, i);
    while (j_ < c_ && is0(mat(rk, j_))) ++j_;
    if (j_ == c_) break;
    for (u32 j = rk + 1; j < mat.row(); ++j) {
      if (is0(mat(j, j_))) continue;
      while (true) {
        if (is0(mat(j, j_))) break;
        T _ = div(mat(rk, j_), mat(j, j_));
        for (u32 k = j_; k < c_; ++k) mat(rk, k) -= _ * mat(j, k);
        mat.swap_row(rk, j);
        neg ^= 1;
      }
    }
    if (clear_u && !is0(mat(rk, j_)))
      for (u32 j = 0; j < rk; ++j) {
        if (is0(mat(j, j_))) continue;
        if (T _ = div(mat(j, j_), mat(rk, j_)); !is0(_))
          for (u32 k = j_; k < c_; ++k) mat(j, k) -= _ * mat(rk, k);
      }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i32)rk) : (i32)rk;
}

}  // namespace tifa_libs::math

#endif