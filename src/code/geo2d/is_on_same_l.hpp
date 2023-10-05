#ifndef TIFA_LIBS_GEO2D_IS_ON_SAME_L
#define TIFA_LIBS_GEO2D_IS_ON_SAME_L

#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
constexpr bool is_on_same_L(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return is_zero(cross(p1, p2, p3)); }

}  // namespace tifa_libs::geo

#endif