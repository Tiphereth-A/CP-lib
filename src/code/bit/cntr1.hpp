#ifndef TIFA_LIBS_BIT_CNTR1
#define TIFA_LIBS_BIT_CNTR1

#include "../util/util.hpp"

#include "cntr0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr int cntr1(T x) { return cntr0(~x); }

}  // namespace tifa_libs::bit

#endif