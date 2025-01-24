#ifndef TIFALIBS_MATH_SAFE_MOD
#define TIFALIBS_MATH_SAFE_MOD

#include "../util/traits.hpp"

namespace tifa_libs::math {

template <sint_c T>
CEXP T safe_mod(T x, to_uint_t<T> mod) NE { return ((x %= (T)mod) < 0 ? x + (T)mod : x); }

}  // namespace tifa_libs::math

#endif