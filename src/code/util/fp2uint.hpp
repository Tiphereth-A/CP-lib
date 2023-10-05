#ifndef TIFA_LIBS_GEO2D_FP2UINT
#define TIFA_LIBS_GEO2D_FP2UINT

#include "util.hpp"

namespace tifa_libs::geo {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
template <class FP>
constexpr u64 fp2uint(FP x, FP eps) { return x + eps; }
#pragma GCC diagnostic pop

}  // namespace tifa_libs::geo

#endif