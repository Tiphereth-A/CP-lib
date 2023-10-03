#ifndef TIFA_LIBS_MATH_MAT_DET
#define TIFA_LIBS_MATH_MAT_DET

#include "../util/util.hpp"

#include "../util/abs_constexpr.hpp"

namespace tifa_libs::math {

template <class Mat, class T = typename Mat::value_type, class Ge>
T det(Mat mat, Ge ge) {
  size_t n = mat.row();
  assert(n == mat.col());
  i64 rk_ = ge(mat, false);
  if ((size_t)abs(rk_) != n) return T{};
  T ret = mat(0, 0);
  for (size_t i = 1; i < n; ++i) ret *= mat(i, i);
  return rk_ < 0 ? -ret : ret;
}

}  // namespace tifa_libs::math

#endif