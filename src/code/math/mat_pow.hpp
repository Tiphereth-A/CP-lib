#ifndef TIFA_LIBS_MATH_MAT_POW
#define TIFA_LIBS_MATH_MAT_POW

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T>
inline matrix<T> pow(matrix<T> mat, size_t b) {
  size_t n = mat.row();
  assert(n == mat.col());
  matrix<T> res(n, n);
  for (size_t i = 0; i < n; ++i) res(i, i) = 1;
  for (; b; b >>= 1, mat *= mat)
    if (b & 1) res *= mat;
  return res;
}

}  // namespace tifa_libs::math

#endif