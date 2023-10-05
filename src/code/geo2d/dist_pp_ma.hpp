#ifndef TIFA_LIBS_GEO2D_DIST_PP_MA
#define TIFA_LIBS_GEO2D_DIST_PP_MA

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points (Manhattan)
template <class FP>
constexpr FP dist_PP_Ma(point<FP> const &lhs, point<FP> const &rhs) { return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y); }

}  // namespace tifa_libs::geo

#endif