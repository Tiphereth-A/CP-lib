#ifndef TIFA_LIBS_GEO2D_ANG_PP
#define TIFA_LIBS_GEO2D_ANG_PP

#include "point.hpp"

namespace tifa_libs::geo2d {

// clamp angle of two points
template <class FP>
constexpr FP ang_PP(point<FP> const &p1, point<FP> const &p2) { return std::atan2(p1 ^ p2, p1 * p2); }

}  // namespace tifa_libs::geo2d

#endif