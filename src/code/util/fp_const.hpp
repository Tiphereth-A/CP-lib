#ifndef TIFA_LIBS_UTIL_FP_CONST
#define TIFA_LIBS_UTIL_FP_CONST

#include "util.hpp"

namespace tifa_libs {

// const FP EPS = std::sqrt(std::numeric_limits<FP>::epsilon());
template <class FP>
constexpr FP EPS = 1e-8;
template <class FP>
const FP PI = std::acos((FP)-1);

}  // namespace tifa_libs

#endif