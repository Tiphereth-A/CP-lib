#ifndef TIFALIBS_LALG_INV_MAT
#define TIFALIBS_LALG_INV_MAT

#include "merge_lr_mat.hpp"

namespace tifa_libs::math {

template <class T, class Is0, class Ge>
requires requires(Is0 is0, Ge ge, T t, matrix<T> A, bool clear_u) {
  { is0(t) } -> std::same_as<bool>;
  { ge(A, clear_u) } -> std::same_as<i32>;
}
constexpr std::optional<matrix<T>> inv_mat(matrix<T> const& mat, Is0&& is0, Ge&& ge) {
  u32 n = mat.row();
  if (n != mat.col()) return {};
  matrix<T> ret(n, n);
  for (u32 i = 0; i < n; ++i) ret(i, i) = 1;
  if ((u64)abs(ge(ret = merge_lr_mat(mat, ret), true)) != n) return {};
  for (u32 i = 0; i < n; ++i)
    if (is0(ret(i, i))) return {};
  ret.apply_range(0, n, n, n * 2, [&ret](u32 i, u32, T& val) { val /= ret(i, i); });
  return ret.submat(0, n, n, n * 2);
}

}  // namespace tifa_libs::math

#endif