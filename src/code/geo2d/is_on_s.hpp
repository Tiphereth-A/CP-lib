#ifndef TIFA_LIBS_GEO2D_IS_ON_S
#define TIFA_LIBS_GEO2D_IS_ON_S

#include "is_on_same_l.hpp"
#include "line.hpp"
#include "point_is_in_middle.hpp"

namespace tifa_libs::geo2d {

//! containing endpoints
template <class FP>
constexpr bool is_on_S(line<FP> const &s1, point<FP> const &p) { return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r); }
//! NOT containing endpoints
template <class FP>
constexpr bool is_on_S_strict(line<FP> const &s1, point<FP> const &p) { return sgn_cross(s1.l, s1.r, p) == 0 && sgn((p - s1.l) * (s1.l - s1.r)) * sgn((p - s1.r) * (s1.l - s1.r)) < 0; }

}  // namespace tifa_libs::geo2d

#endif