#ifndef TIFA_LIBS_BIT_LOG2
#define TIFA_LIBS_BIT_LOG2

#include "cntl0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr int log2(T x) {
  if (x == 0) return -1;
  return (int)sizeof(T) * 8 - cntl0(x >> 1);
}

}  // namespace tifa_libs::bit

#endif