#ifndef TIFA_LIBS_MATH_MAT_INV
#define TIFA_LIBS_MATH_MAT_INV

#include "../util/util.hpp"

#include "mat_merge_lr.hpp"

namespace tifa_libs::math {

template <class Mat, class Is0, class Ge, class T = typename Mat::value_type>
inline std::optional<Mat> inverse(Mat const &mat, Is0 is0, Ge ge) {
  size_t n = mat.row();
  if (n != mat.col()) return {};
  Mat ret(n, n);
  for (size_t i = 0; i < n; ++i) ret(i, i) = 1;
  if ((u64)abs(ge(ret = merge_lr(mat, ret), true)) != n) return {};
  for (size_t i = 0; i < n; ++i)
    if (is0(ret(i, i))) return {};
  ret.apply_range(0, n, n, n * 2, [&ret](size_t i, [[maybe_unused]] size_t j, T &val) { val /= ret(i, i); });
  return ret.submat(0, n, n, n * 2);
}

}  // namespace tifa_libs::math

#endif