#ifndef TIFA_LIBS_MATH_MAT_UHB
#define TIFA_LIBS_MATH_MAT_UHB

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T, class Is0>
inline void uhb(matrix<T> &mat, Is0 is0) {
  size_t n = mat.row();
  assert(n == mat.col());
  if (n <= 2) return;
  for (size_t i = 0, p; i < n - 2; ++i) {
    p = i + 1;
    for (; p != n; ++p)
      if (!is0(mat(p, i))) break;
    if (p == n) continue;
    if (p != i + 1) {
      mat.swap_row(p, i + 1);
      mat.swap_col(p, i + 1);
    }
    for (size_t j = i + 2; j < n; ++j) {
      if (is0(mat(j, i))) continue;
      T _ = mat(j, i) / mat(i + 1, i);
      for (size_t k = i; k < n; ++k) mat(j, k) -= _ * mat(i + 1, k);
      for (size_t k = 0; k < n; ++k) mat(k, i + 1) += _ * mat(k, j);
    }
  }
}

}  // namespace tifa_libs::math

#endif