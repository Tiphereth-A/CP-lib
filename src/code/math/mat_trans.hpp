#ifndef TIFA_LIBS_MATH_MAT_TRANS
#define TIFA_LIBS_MATH_MAT_TRANS

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T>
inline matrix<T> transpose(matrix<T> const &mat) {
  size_t r_ = mat.row(), c_ = mat.col();
  matrix<T> ret(c_, r_);
  ret.apply(0, c_, 0, r_, [&mat](size_t i, size_t j, T &val) { val = mat(j, i); });
  return ret;
}

}  // namespace tifa_libs::math

#endif