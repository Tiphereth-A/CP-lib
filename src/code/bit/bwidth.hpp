#ifndef TIFA_LIBS_BIT_BWIDTH
#define TIFA_LIBS_BIT_BWIDTH

#include "cntl0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr int bwidth(T x) { return (int)sizeof(T) * 8 - cntl0(x); }

}  // namespace tifa_libs::bit

#endif