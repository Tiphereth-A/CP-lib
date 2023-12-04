#ifndef TIFALIBS_BIT_BWIDTH
#define TIFALIBS_BIT_BWIDTH

#include "cntl0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <class T>
constexpr int bwidth(T x) { return (int)sizeof(T) * 8 - cntl0(x); }

}  // namespace tifa_libs::bit

#endif