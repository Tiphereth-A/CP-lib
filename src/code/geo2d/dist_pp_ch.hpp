#ifndef TIFALIBS_GEO2D_DIST_PP_CH
#define TIFALIBS_GEO2D_DIST_PP_CH

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Chebyshev)
template <class FP>
constexpr FP dist_PP_Ch(point<FP> const &p1, point<FP> const &p2) { return std::max(std::abs(p1.x - p2.x), std::abs(p1.y - p2.y)); }

}  // namespace tifa_libs::geo

#endif