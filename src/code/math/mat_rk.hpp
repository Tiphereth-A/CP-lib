#ifndef TIFA_LIBS_MATH_MAT_RK
#define TIFA_LIBS_MATH_MAT_RK

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

template <class T, class Ge>
inline u64 rank(matrix<T> const &mat, Ge ge) { return (u64)abs(ge(matrix<T>(mat), false)); }

}  // namespace tifa_libs::math

#endif