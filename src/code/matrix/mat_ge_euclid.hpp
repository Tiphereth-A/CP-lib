#ifndef TIFALIBS_MATRIX_MAT_GE_EUCLID
#define TIFALIBS_MATRIX_MAT_GE_EUCLID

#include "mat_ge_swapr_.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0, class Div, class T = typename Mat::value_type>
i32 ge_euclid(Mat &mat, Is0 is0, Div div, u32 row_start, u32 row_end, bool clear_u = true) {
  assert(row_start < row_end && row_end <= mat.row());
  u32 r_ = row_end - row_start, c_ = mat.col(), rk_max = std::min(r_, c_);
  u32 rk = 0;
  bool neg = false;
  for (u32 i = row_start, now_row = row_start, j_ = i; i < row_end; ++i) {
    neg ^= ge_impl_::swapr__(mat, now_row, rk, row_end);
    j_ = std::max(j_, i);
    while (j_ < c_ && is0(mat(rk, j_))) ++j_;
    if (j_ == c_) break;
    for (u32 j = rk + 1; j < row_end; ++j) {
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
template <class Mat, class Is0, class Div, class T = typename Mat::value_type>
i32 ge_euclid(Mat &mat, Is0 is0, Div div, bool clear_u = true) { return ge_euclid<Mat, Is0, Div, T>(mat, is0, div, 0, mat.row(), clear_u); }

}  // namespace tifa_libs::math

#endif