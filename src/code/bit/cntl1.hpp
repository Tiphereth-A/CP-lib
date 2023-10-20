#ifndef TIFA_LIBS_BIT_CNTL1
#define TIFA_LIBS_BIT_CNTL1

#include "cntl0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <class T>
constexpr int cntl1(T x) { return cntl0(~x); }

}  // namespace tifa_libs::bit

#endif