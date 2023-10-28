#ifndef TIFA_LIBS_MATH_SAFE_MOD
#define TIFA_LIBS_MATH_SAFE_MOD

#include "../util/traits.hpp"

namespace tifa_libs::math {

template <class T, std::enable_if_t<is_sint<T>::value>* = nullptr>
constexpr T safe_mod(T x, typename to_uint<T>::type mod) { return ((x %= (T)mod) < 0 ? x + (T)mod : x); }

}  // namespace tifa_libs::math

#endif