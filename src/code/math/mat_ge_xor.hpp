#ifndef TIFA_LIBS_MATH_MAT_GE_XOR
#define TIFA_LIBS_MATH_MAT_GE_XOR

#include "../util/util.hpp"

#include "mat.hpp"
#include "mat_ge_swapr_.hpp"

namespace tifa_libs::math {

template <class Is0>
inline i64 ge_xor(matrix<bool> &mat, [[maybe_unused]] Is0 is_0, size_t row_start, size_t row_end, bool clear_u = true) {
  assert(row_start < row_end && row_end <= mat.row());
  size_t r_ = row_end - row_start, c_ = mat.col(), rk_max = std::min(r_, c_);
  u64 rk = 0;
  bool neg = false;
  for (size_t i = row_start, now_row = row_start, j_ = i; i < row_end; ++i) {
    j_ = std::max(j_, i);
    if (!mat(rk, i)) {
      neg ^= ge_detail__::swapr__(mat, now_row, rk, row_end);
      while (j_ < c_ && !mat(rk, j_)) ++j_;
      if (j_ == c_) break;
    }
    for (u64 j = clear_u ? 0 : rk + 1; j < row_end; ++j) {
      if (j == rk || !mat(j, j_)) continue;
      mat(j, j_) = false;
      for (size_t k = j_ + 1; k < c_; ++k)
        if (mat(rk, k)) mat(j, k) = !mat(j, k);
    }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i64)rk) : (i64)rk;
}

template <class Is0>
inline i64 ge_xor(matrix<bool> &mat, Is0 is_0, bool clear_u = true) { return ge_xor(mat, is_0, 0, mat.row(), clear_u); }

}  // namespace tifa_libs::math

#endif