#ifndef TIFA_LIBS_MATH_MAT_INV
#define TIFA_LIBS_MATH_MAT_INV

#include "../util/util.hpp"

#include "mat.hpp"
#include "mat_merge_lr.hpp"

namespace tifa_libs::math {

template <class T, class Ge>
inline std::optional<matrix<T>> inverse(matrix<T> const &mat, Ge ge) {
  size_t n = mat.row();
  if (n != mat.col()) return {};
  matrix<T> ret(n, n);
  for (size_t i = 0; i < n; ++i) ret(i, i) = 1;
  if ((u64)abs(ge(ret = merge_lr(mat, ret), true)) != n) return {};
  ret.apply(0, n, n, n * 2, [&ret](size_t i, [[maybe_unused]] size_t j, T &val) { val /= ret(i, i); });
  return ret.submat(0, n, n, n * 2);
}

}  // namespace tifa_libs::math

#endif