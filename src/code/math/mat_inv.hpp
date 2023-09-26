#ifndef TIFA_LIBS_MATH_MAT_INV
#define TIFA_LIBS_MATH_MAT_INV

#include "../util/util.hpp"

#include "mat.hpp"
#include "mat_merge_lr.hpp"

namespace tifa_libs::math {

template <class T, class Is0, class Ge>
inline std::optional<matrix<T>> mat_inv(matrix<T> const &mat, Is0 is0, Ge ge) {
  size_t n = mat.row();
  if (n != mat.col()) return {};
  matrix<T> ret(n, n);
  for (size_t i = 0; i < n; ++i) ret(i, i) = 1;
  if ((u64)abs(ge(ret = mat_merge_lr(mat, ret), true)) != n) return {};
  for (size_t i = 0; i < n; ++i)
    if (is0(ret(i, i))) return {};
  ret.apply(0, n, n, n * 2, [&ret](size_t i, [[maybe_unused]] size_t j, T &val) { val /= ret(i, i); });
  return ret.submat(0, n, n, n * 2);
}

}  // namespace tifa_libs::math

#endif