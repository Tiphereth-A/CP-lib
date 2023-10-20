#ifndef TIFA_LIBS_MATH_MAT_GE_XOR
#define TIFA_LIBS_MATH_MAT_GE_XOR

#include "mat_ge_swapr_.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0>
inline i64 ge_xor(Mat &mat, [[maybe_unused]] Is0 is0, usz row_start, usz row_end, bool clear_u = true) {
  static_assert(std::is_same_v<typename Mat::value_type, bool>);
  assert(row_start < row_end && row_end <= mat.row());
  usz r_ = row_end - row_start, c_ = mat.col(), rk_max = std::min(r_, c_);
  u64 rk = 0;
  bool neg = false;
  for (usz i = row_start, now_row = row_start, j_ = i; i < row_end; ++i) {
    j_ = std::max(j_, i);
    if (!mat(rk, i)) {
      neg ^= ge_impl_::swapr__(mat, now_row, rk, row_end);
      while (j_ < c_ && !mat(rk, j_)) ++j_;
      if (j_ == c_) break;
    }
    for (u64 j = clear_u ? 0 : rk + 1; j < row_end; ++j) {
      if (j == rk || !mat(j, j_)) continue;
      mat(j, j_) = false;
      for (usz k = j_ + 1; k < c_; ++k)
        if (mat(rk, k)) mat(j, k) = !mat(j, k);
    }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i64)rk) : (i64)rk;
}

template <class Mat, class Is0>
inline i64 ge_xor(Mat &mat, Is0 is0, bool clear_u = true) { return ge_xor(mat, is0, 0, mat.row(), clear_u); }

}  // namespace tifa_libs::math

#endif