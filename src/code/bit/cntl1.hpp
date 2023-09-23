#ifndef TIFA_LIBS_BIT_CNTL1
#define TIFA_LIBS_BIT_CNTL1

#include "../util/util.hpp"

#include "cntl0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr int cntl1(T x) { return cntl0(~x); }

}  // namespace tifa_libs::bit

#endif