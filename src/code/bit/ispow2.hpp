#ifndef TIFA_LIBS_BIT_ISPOW2
#define TIFA_LIBS_BIT_ISPOW2

#include "popcnt.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <class T>
constexpr bool ispow2(T x) { return popcnt(x) == 1; }

}  // namespace tifa_libs::bit

#endif