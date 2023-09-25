#ifndef TIFA_LIBS_MATH_MAT_GE_EUCLID
#define TIFA_LIBS_MATH_MAT_GE_EUCLID

#include "../util/util.hpp"

#include "mat.hpp"
#include "mat_ge_swapr_.hpp"

namespace tifa_libs::math {

template <class T, class Is0>
inline i64 ge_euclid(matrix<T> &mat, Is0 is_0, size_t row_start, size_t row_end, bool clear_u = true) {
  assert(row_start < row_end && row_end <= mat.row());
  size_t r_ = row_end - row_start, c_ = mat.col(), rk_max = std::min(r_, c_);
  u64 rk = 0;
  bool neg = false;
  for (size_t i = row_start, now_row = row_start; i < row_end; ++i) {
    neg ^= ge_detail__::swapr__(mat, now_row, rk, row_end);
    size_t j_ = i;
    while (j_ < c_ && is_0(mat(rk, j_))) ++j_;
    if (j_ == c_) break;
    for (u64 j = clear_u ? 0 : rk; j < row_end; ++j) {
      if (j == rk || is_0(mat(j, j_))) continue;
      while (true) {
        T _ = mat(j, j_) / mat(rk, j_);
        for (size_t k = 0; k < c_; ++k) mat(j, k) -= mat(rk, k);
        if (!is_0(mat(j, j_))) {
          mat.swap_row(rk, j);
          neg ^= 1;
        } else
          break;
      }
    }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i64)rk) : (i64)rk;
}
template <class T, class Is0>
inline i64 ge_euclid(matrix<T> &mat, Is0 is_0, bool clear_u = true) { return ge_euclid(mat, is_0, 0, mat.row(), clear_u); }

}  // namespace tifa_libs::math

#endif