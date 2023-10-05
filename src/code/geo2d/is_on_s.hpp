#ifndef TIFA_LIBS_GEO2D_IS_ON_S
#define TIFA_LIBS_GEO2D_IS_ON_S

#include "is_on_same_l.hpp"
#include "line.hpp"
#include "point_is_in_middle.hpp"

namespace tifa_libs::geo {

//! containing endpoints
template <class FP>
constexpr bool is_on_S(line<FP> const &s, point<FP> const &p) { return is_on_same_L(s.l, s.r, p) && is_in_middle(s.l, p, s.r); }
//! NOT containing endpoints
template <class FP>
constexpr bool is_on_S_strict(line<FP> const &s, point<FP> const &p) { return sgn_cross(s.l, s.r, p) == 0 && sgn((p - s.l) * (s.l - s.r)) * sgn((p - s.r) * (s.l - s.r)) < 0; }

}  // namespace tifa_libs::geo

#endif