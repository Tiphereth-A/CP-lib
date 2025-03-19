#ifndef TIFALIBS_LALG_UHB_MAT
#define TIFALIBS_LALG_UHB_MAT

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0>
requires requires(Is0 is0, TPN Mat::val_t t) {
  { is0(t) } -> std::same_as<bool>;
}
CEXP void uhb(Mat &mat, Is0 &&is0) NE {
  const u32 n = mat.row();
  if (assert(n == mat.col()); n <= 2) return;
  for (u32 i = 0, p; i < n - 2; ++i) {
    for (p = i + 1; p != n; ++p)
      if (!is0(mat(p, i))) break;
    if (p == n) continue;
    if (p != i + 1) mat.swap_row(p, i + 1), mat.swap_col(p, i + 1);
    flt_ (u32, j, i + 2, n) {
      if (is0(mat(j, i))) continue;
      const auto _ = mat(j, i) / mat(i + 1, i);
      flt_ (u32, k, i, n) mat(j, k) -= _ * mat(i + 1, k);
      flt_ (u32, k, 0, n) mat(k, i + 1) += _ * mat(k, j);
    }
  }
}

}  // namespace tifa_libs::math

#endif