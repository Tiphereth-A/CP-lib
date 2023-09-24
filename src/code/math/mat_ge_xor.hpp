#ifndef TIFA_LIBS_MATH_MAT_GE_XOR
#define TIFA_LIBS_MATH_MAT_GE_XOR

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class Is0>
inline i64 ge_xor(matrix<bool> &mat, [[maybe_unused]] Is0 is_0, size_t row_start, size_t row_end, bool clear_u = true) {
  assert(row_start < row_end && row_end <= mat.row_size());
  u64 rk = 0;
  bool neg = false;
  for (size_t i = row_start; i < std::min(row_end, mat.col_size()); ++i) {
    if (!mat(rk, i)) {
      for (size_t j = rk + 1; j < row_end; ++j)
        if (mat(j, i)) {
          mat.swap_row(j, rk);
          neg ^= true;
          break;
        }
      if (!mat(rk, i)) continue;
    }
    std::valarray<bool> tmp_ = mat.data()[std::slice(rk * mat.col_size() + i + 1, mat.col_size() - i - 1, 1)];
    for (u64 j = clear_u ? 0 : rk + 1; j < row_end; ++j) {
      if (j == rk || !mat(j, i)) continue;
      mat(j, i) = false;
      mat.data()[std::slice(j * mat.col_size() + i + 1, mat.col_size() - i - 1, 1)] ^= tmp_;
    }
    ++rk;
  }
  return neg ? -((i64)rk) : (i64)rk;
}
template <class Is0>
inline i64 ge_xor(matrix<bool> &mat, Is0 is_0, bool clear_u = true) { return ge_xor(mat, is_0, 0, mat.row_size(), clear_u); }

}  // namespace tifa_libs::math

#endif