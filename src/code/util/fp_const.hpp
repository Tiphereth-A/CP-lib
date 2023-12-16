#ifndef TIFALIBS_UTIL_FP_CONST
#define TIFALIBS_UTIL_FP_CONST

#include "util.hpp"

namespace tifa_libs {

using namespace std::numbers;

// std::sqrt(std::numeric_limits<FP>::epsilon())
template <std::floating_point FP>
constexpr inline FP eps_v = FP(1e-8L);

}  // namespace tifa_libs

#endif