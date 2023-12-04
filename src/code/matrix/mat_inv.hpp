#ifndef TIFALIBS_MATRIX_MAT_INV
#define TIFALIBS_MATRIX_MAT_INV

#include "mat_merge_lr.hpp"

namespace tifa_libs::math {

template <class T, class Is0, class Ge>
std::optional<matrix<T>> mat_inv(matrix<T> const &mat, Is0 is0, Ge ge) {
  u32 n = mat.row();
  if (n != mat.col()) return {};
  matrix<T> ret(n, n);
  for (u32 i = 0; i < n; ++i) ret(i, i) = 1;
  if ((u64)abs(ge(ret = mat_merge_lr(mat, ret), true)) != n) return {};
  for (u32 i = 0; i < n; ++i)
    if (is0(ret(i, i))) return {};
  ret.apply_range(0, n, n, n * 2, [&ret](u32 i, u32, T &val) { val /= ret(i, i); });
  return ret.submat(0, n, n, n * 2);
}

}  // namespace tifa_libs::math

#endif