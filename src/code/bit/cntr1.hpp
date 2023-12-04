#ifndef TIFALIBS_BIT_CNTR1
#define TIFALIBS_BIT_CNTR1

#include "cntr0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <class T>
constexpr int cntr1(T x) { return cntr0(~x); }

}  // namespace tifa_libs::bit

#endif