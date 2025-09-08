#ifndef TIFALIBS_GEO2D_TAN_CP
#define TIFALIBS_GEO2D_TAN_CP

#include "circle.hpp"

namespace tifa_libs::geo {

// tagante points of point to circle
// maybe duplicate
template <class FP>
CEXP auto tan_CP(circle<FP> CR c, point<FP> CR p) NE {
  std::optional<ptt<point<FP>>> ret;
  point v = p - c.o;
  const FP x = v.norm2(), d = x - c.r * c.r;
  if (is_neg(d)) return ret;
  const point q1 = c.o + v * (c.r * c.r / x), q2 = v.do_rot90() * (c.r * std::sqrt(d) / x);
  // counter clock-wise
  ret.emplace(q1 - q2, q1 + q2);
  return ret;
}

}  // namespace tifa_libs::geo

#endif