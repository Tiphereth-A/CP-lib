#ifndef TIFALIBS_LALG_INV_MAT
#define TIFALIBS_LALG_INV_MAT

#include "merge_lr_mat.hpp"

namespace tifa_libs::math {

template <class T, class Is0, class Ge, bool calc_det = false>
requires requires(Is0 is0, Ge ge, T t, matrix<T> A, bool clear_u) {
  { is0(t) } -> std::same_as<bool>;
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP auto inv_mat(matrix<T> CR mat, Is0&& is0, Ge&& ge) NE
    -> std::conditional_t<calc_det, std::optional<std::pair<T, matrix<T>>>, std::optional<matrix<T>>> {
  const u32 n = mat.row();
  if (n != mat.col()) return {};
  matrix<T> ret(n, n);
  flt_ (u32, i, 0, n) ret(i, i) = 1;
  auto rk = ge(ret = merge_lr_mat(mat, ret), true);
  if ((u64)abs(rk) != n) return {};
  flt_ (u32, i, 0, n)
    if (is0(ret(i, i))) return {};
  if CEXP (!std::is_same_v<T, bool>) ret.apply_range(0, n, n, n * 2, [&ret](u32 i, u32, T& val) NE { val /= ret(i, i); });
  if CEXP (calc_det) {
    T det{ret(0, 0)};
    flt_ (u32, i, 1, n) det *= ret(i, i);
    return {{rk < 0 ? -det : det, ret.submat(0, n, n, n * 2)}};
  } else return ret.submat(0, n, n, n * 2);
}

}  // namespace tifa_libs::math

#endif