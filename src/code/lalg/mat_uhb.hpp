#ifndef TIFALIBS_LALG_MAT_UHB
#define TIFALIBS_LALG_MAT_UHB

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0, class T = typename Mat::value_type>
constexpr void uhb(Mat &mat, Is0 is0) {
  u32 n = mat.row();
  assert(n == mat.col());
  if (n <= 2) return;
  for (u32 i = 0, p; i < n - 2; ++i) {
    p = i + 1;
    for (; p != n; ++p)
      if (!is0(mat(p, i))) break;
    if (p == n) continue;
    if (p != i + 1) {
      mat.swap_row(p, i + 1);
      mat.swap_col(p, i + 1);
    }
    for (u32 j = i + 2; j < n; ++j) {
      if (is0(mat(j, i))) continue;
      T _ = mat(j, i) / mat(i + 1, i);
      for (u32 k = i; k < n; ++k) mat(j, k) -= _ * mat(i + 1, k);
      for (u32 k = 0; k < n; ++k) mat(k, i + 1) += _ * mat(k, j);
    }
  }
}

}  // namespace tifa_libs::math

#endif