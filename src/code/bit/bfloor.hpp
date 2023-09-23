#ifndef TIFA_LIBS_BIT_BFLOOR
#define TIFA_LIBS_BIT_BFLOOR

#include "../util/util.hpp"

#include "cntl0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr T bfloor(T x) {
  if (x == 0) return 0;
  return (T)1u << (sizeof(T) * 8 - cntl0(x >> 1));
}

}  // namespace tifa_libs::bit

#endif