#ifndef TIFA_LIBS_GEO2D_DIST_PP_CH
#define TIFA_LIBS_GEO2D_DIST_PP_CH

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Chebyshev)
template <class FP>
constexpr FP dist_PP_Ch(point<FP> const &lhs, point<FP> const &rhs) { return std::max(std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y)); }

}  // namespace tifa_libs::geo

#endif