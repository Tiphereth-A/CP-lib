#ifndef TIFA_LIBS_MATH_MATRIX_POW
#define TIFA_LIBS_MATH_MATRIX_POW

#include "../util/util.hpp"

#include "matrix.hpp"

namespace tifa_libs::math {

// [lhs] [rhs] -> [lhs; rhs]
template <class T, class Isz = std::function<bool(T)>>
inline matrix<T, Isz> pow(matrix<T, Isz> mat, size_t b) {
  matrix<T, Isz> res(mat.row_size(), mat.col_size(), mat.iszero, T{});
  res.diag(0) = 1;
  for (; b; b >>= 1, mat *= mat)
    if (b & 1) res *= mat;
  return res;
}

}  // namespace tifa_libs::math

#endif