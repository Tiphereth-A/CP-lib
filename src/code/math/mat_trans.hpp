#ifndef TIFA_LIBS_MATH_MAT_TRANS
#define TIFA_LIBS_MATH_MAT_TRANS

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T>
inline matrix<T> transpose(matrix<T> const &mat) {
  matrix<T> ret(mat.col_size(), mat.row_size());
  for (size_t i = 0; i < mat.row_size(); ++i) ret.col(i) = mat.crow(i);
  return ret;
}

}  // namespace tifa_libs::math

#endif