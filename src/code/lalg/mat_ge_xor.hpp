#ifndef TIFALIBS_LALG_MAT_GE_XOR
#define TIFALIBS_LALG_MAT_GE_XOR

#include "mat_ge_swapr_.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0>
requires std::same_as<typename Mat::value_type, bool>
constexpr i32 ge_xor(Mat &mat, Is0, u32 row_start, u32 row_end, bool clear_u = true) {
  assert(row_start < row_end && row_end <= mat.row());
  u32 r_ = row_end - row_start, c_ = mat.col(), rk_max = std::min(r_, c_);
  u32 rk = 0;
  bool neg = false;
  for (u32 i = row_start, now_row = row_start, j_ = i; i < row_end; ++i) {
    j_ = std::max(j_, i);
    if (!mat(rk, i)) {
      neg ^= ge_impl_::swapr__(mat, now_row, rk, row_end);
      while (j_ < c_ && !mat(rk, j_)) ++j_;
      if (j_ == c_) break;
    }
    for (u32 j = clear_u ? 0 : rk + 1; j < row_end; ++j) {
      if (j == rk || !mat(j, j_)) continue;
      mat(j, j_) = false;
      for (u32 k = j_ + 1; k < c_; ++k)
        if (mat(rk, k)) mat(j, k) = !mat(j, k);
    }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i32)rk) : (i32)rk;
}

template <class Mat, class Is0>
i32 ge_xor(Mat &mat, Is0 is0, bool clear_u = true) { return ge_xor(mat, is0, 0, mat.row(), clear_u); }

}  // namespace tifa_libs::math

#endif