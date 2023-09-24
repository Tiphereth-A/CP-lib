#ifndef TIFA_LIBS_MATH_MAT_POW
#define TIFA_LIBS_MATH_MAT_POW

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T>
inline matrix<T> pow(matrix<T> mat, size_t b) {
  matrix<T> res(mat.row_size(), mat.col_size());
  res.diag(0) = 1;
  for (; b; b >>= 1, mat *= mat)
    if (b & 1) res *= mat;
  return res;
}

}  // namespace tifa_libs::math

#endif