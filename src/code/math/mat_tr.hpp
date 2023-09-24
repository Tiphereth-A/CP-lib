#ifndef TIFA_LIBS_MATH_MAT_TR
#define TIFA_LIBS_MATH_MAT_TR

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T>
inline T trace(matrix<T> const &mat) { return mat.diag(0).sum(); }

}  // namespace tifa_libs::math

#endif