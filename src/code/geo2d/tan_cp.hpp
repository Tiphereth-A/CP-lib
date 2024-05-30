#ifndef TIFALIBS_GEO2D_TAN_CP
#define TIFALIBS_GEO2D_TAN_CP

#include "circle.hpp"

namespace tifa_libs::geo {

// tagante points of point to circle
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<point<FP>>> tan_CP(circle<FP> CR c, point<FP> CR p) {
  point v = p - c.o;
  const FP x = v.norm2(), d = x - c.r * c.r;
  if (is_neg(d)) return {};
  const point q1 = c.o + v * (c.r * c.r / x), q2 = v.do_rot90() * (c.r * std::sqrt(d) / x);
  // counter clock-wise
  return ptt<point<FP>>{q1 - q2, q1 + q2};
}

}  // namespace tifa_libs::geo

#endif