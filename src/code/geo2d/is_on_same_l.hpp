#ifndef TIFALIBS_GEO2D_IS_ON_SAME_L
#define TIFALIBS_GEO2D_IS_ON_SAME_L

#include "cross.hpp"
#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP bool is_on_same_L(point<FP> CR p1, point<FP> CR p2, point<FP> CR p3) { return is_zero(cross(p1, p2, p3)); }

}  // namespace tifa_libs::geo

#endif