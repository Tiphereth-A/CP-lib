#ifndef TIFA_LIBS_MATH_SAFE_MOD
#define TIFA_LIBS_MATH_SAFE_MOD

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, std::enable_if_t<std::is_signed_v<T>, int> = 0>
constexpr T safe_mod(T x, std::make_unsigned_t<T> mod) { return ((x %= (T)mod) < 0 ? x + (T)mod : x); }

}  // namespace tifa_libs::math

#endif