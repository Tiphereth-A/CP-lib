#ifndef TIFALIBS_GEO2D_INV_P2P
#define TIFALIBS_GEO2D_INV_P2P

#include "circle.hpp"

namespace tifa_libs::geo {

// geometry inverse of a point
template <class FP>
constexpr point<FP> inv_P2P(circle<FP> const &c, point<FP> const &p) {
  point v = p - c.o;
  return c.o + v * (c.r * c.r / v.norm2());
}

}  // namespace tifa_libs::geo

#endif