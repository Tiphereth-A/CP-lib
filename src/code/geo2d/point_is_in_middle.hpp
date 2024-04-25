#ifndef TIFALIBS_GEO2D_POINT_IS_IN_MIDDLE
#define TIFALIBS_GEO2D_POINT_IS_IN_MIDDLE

#include "../util/fp_range_is_in_middle.hpp"
#include "point.hpp"

namespace tifa_libs::geo {

//! containing endpoints
template <class FP>
CEXP bool is_in_middle(point<FP> CR a, point<FP> CR m, point<FP> CR b) { return tifa_libs::is_in_middle(a.x, m.x, b.x) && tifa_libs::is_in_middle(a.y, m.y, b.y); }

}  // namespace tifa_libs::geo

#endif