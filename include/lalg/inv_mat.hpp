#ifndef TIFALIBS_LALG_INV_MAT
#define TIFALIBS_LALG_INV_MAT

#include "merge_lr_mat.hpp"

namespace tifa_libs::math {

template <class T, class Is0, class Ge, bool calc_det = false>
requires requires(Is0 is0, Ge ge, T t, matrix<T> A, bool clear_u) {
  { is0(t) } -> std::same_as<bool>;
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP auto inv_mat(matrix<T> CR mat, Is0&& is0, Ge&& ge) NE {
  const u32 n = mat.row();
  std::optional<std::conditional_t<calc_det, std::pair<T, matrix<T>>, matrix<T>>> ret;
  if (n != mat.col()) return ret;
  matrix<T> ans(n, n);
  flt_ (u32, i, 0, n) ans(i, i) = 1;
  auto rk = ge(ans = merge_lr_mat(mat, ans), true);
  if ((u64)abs(rk) != n) return ret;
  flt_ (u32, i, 0, n)
    if (is0(ans(i, i))) return ret;
  if CEXP (!std::is_same_v<T, bool>) ans.apply_range(0, n, n, n * 2, [&ans](u32 i, u32, T& val) NE { val /= ans(i, i); });
  if CEXP (calc_det) {
    T det{ans(0, 0)};
    flt_ (u32, i, 1, n) det *= ans(i, i);
    ret.emplace(rk < 0 ? -det : det, ans.submat(0, n, n, n * 2));
    return ret;
  } else {
    ret.emplace(ans.submat(0, n, n, n * 2));
    return ret;
  }
}

}  // namespace tifa_libs::math

#endif