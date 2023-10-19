#ifndef TIFA_LIBS_BIT_LOG2
#define TIFA_LIBS_BIT_LOG2

#include "bwidth.hpp"

namespace tifa_libs::bit {

template <typename T>
constexpr int log2(T x) { return bwidth(x) - 1; }

}  // namespace tifa_libs::bit

#endif