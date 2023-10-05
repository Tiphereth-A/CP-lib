#ifndef TIFA_LIBS_GEO2D_POINT_IS_IN_MIDDLE
#define TIFA_LIBS_GEO2D_POINT_IS_IN_MIDDLE

#include "point.hpp"

namespace tifa_libs::geo {

//! containing endpoints
template <class FP>
constexpr bool is_in_middle(point<FP> a, point<FP> m, point<FP> b) { return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y); }

}  // namespace tifa_libs::geo

#endif