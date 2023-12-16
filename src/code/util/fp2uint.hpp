#ifndef TIFALIBS_UTIL_FP2UINT
#define TIFALIBS_UTIL_FP2UINT

#include "util.hpp"

namespace tifa_libs {

#pragma GCC diagnostic ignored "-Wfloat-conversion"
template <std::floating_point FP>
constexpr u64 fp2uint(FP x, FP eps) { return x + eps; }
#pragma GCC diagnostic warning "-Wfloat-conversion"

}  // namespace tifa_libs

#endif