#ifndef TIFA_LIBS_MATH_ABS_CONSTEXPR
#define TIFA_LIBS_MATH_ABS_CONSTEXPR

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
constexpr T abs(T x) { return x < 0 ? -x : x; }
template <class T, std::enable_if_t<!std::is_arithmetic_v<T>> * = nullptr>
constexpr T abs(T x) { return x; }

}  // namespace tifa_libs::math

#endif