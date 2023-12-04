#ifndef TIFALIBS_BIT_LOWBIT
#define TIFALIBS_BIT_LOWBIT

#include "cntr0.hpp"

namespace tifa_libs::bit {

template <class T>
constexpr T lowbit(T x) { return T(1) << cntr0(x); }

}  // namespace tifa_libs::bit

#endif