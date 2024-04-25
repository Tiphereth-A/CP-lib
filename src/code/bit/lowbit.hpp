#ifndef TIFALIBS_BIT_LOWBIT
#define TIFALIBS_BIT_LOWBIT

#include "../util/util.hpp"

namespace tifa_libs::bit {

template <class T>
CEXP T lowbit(T x) { return T(1) << std::countr_zero(x); }

}  // namespace tifa_libs::bit

#endif