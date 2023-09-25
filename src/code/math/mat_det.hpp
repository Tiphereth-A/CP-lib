#ifndef TIFA_LIBS_MATH_MAT_DET
#define TIFA_LIBS_MATH_MAT_DET

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T, class Ge>
T det(matrix<T> const &mat, Ge ge) {
  size_t n = mat.row();
  assert(n == mat.col());
  matrix<T> _ = mat;
  i64 rk_ = ge(_, false);
  if ((u64)abs(rk_) != n) return T{};
  T ret = _(0, 0);
  for (size_t i = 1; i < n; ++i) ret *= _(i, i);
  return rk_ < 0 ? -ret : ret;
}

}  // namespace tifa_libs::math

#endif