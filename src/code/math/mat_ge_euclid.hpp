#ifndef TIFA_LIBS_MATH_MAT_GE_EUCLID
#define TIFA_LIBS_MATH_MAT_GE_EUCLID

#include "../util/util.hpp"

#include "mat.hpp"
#include "mat_ge_swapr_.hpp"

namespace tifa_libs::math {

template <class T, class Is0>
inline i64 ge_euclid(matrix<T> &mat, Is0 is_0, size_t row_start, size_t row_end, bool clear_u = true) {
  assert(row_start < row_end && row_end <= mat.row_size());
  u64 rk = 0;
  bool neg = false;
  for (size_t i = row_start, now_row; i < std::min(row_end, mat.col_size()); ++i) {
    neg ^= ge_detail__::swapr__(mat, now_row, rk, i, row_end);
    if (is_0(mat(rk, i))) continue;
    for (u64 j = clear_u ? 0 : rk; j < row_end; ++j) {
      if (j == rk || is_0(mat(j, i))) continue;
      while (true) {
        T _ = mat(j, i) / mat(rk, i);
        mat.row(j) -= _ * mat.crow(rk);
        if (!is_0(mat(j, i))) {
          mat.swap_row(rk, j);
          neg ^= 1;
        } else
          break;
      }
    }
    ++rk;
  }
  return neg ? -((i64)rk) : (i64)rk;
}
template <class T, class Is0>
inline i64 ge_euclid(matrix<T> &mat, Is0 is_0, bool clear_u = true) { return ge_euclid(mat, is_0, 0, mat.row_size(), clear_u); }

}  // namespace tifa_libs::math

#endif