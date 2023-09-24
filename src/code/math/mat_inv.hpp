#ifndef TIFA_LIBS_MATH_MAT_INV
#define TIFA_LIBS_MATH_MAT_INV

#include "../util/util.hpp"

#include "mat.hpp"
#include "mat_merge_lr.hpp"

namespace tifa_libs::math {

template <class T, class Ge>
inline std::optional<matrix<T>> inverse(matrix<T> const &mat, Ge ge) {
  assert(mat.row_size() == mat.col_size());
  matrix<T> ret(mat.row_size(), mat.col_size());
  ret.diag(0) = 1;
  if ((size_t)abs(ge(ret = merge_lr(mat, ret), true)) != mat.row_size()) return {};
  for (size_t i = 0; i < mat.row_size(); ++i) ret.data()[std::slice((i * 2 + 1) * mat.col_size(), mat.col_size(), 1)] /= std::valarray<T>(ret(i, i), mat.col_size());
  ret = ret.submat(0, mat.row_size(), mat.col_size(), mat.col_size() * 2);
  return ret;
}

}  // namespace tifa_libs::math

#endif