#ifndef TIFA_LIBS_GEO2D_DIST_PS
#define TIFA_LIBS_GEO2D_DIST_PS

#include "dist_pp.hpp"
#include "point_is_in_middle.hpp"
#include "proj.hpp"

namespace tifa_libs::geo2d {

// min dist_PP from a point to another point which belongs to a segment
template <class FP>
constexpr FP dist_PS(point<FP> const &p, line<FP> const &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  point h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}

}  // namespace tifa_libs::geo2d

#endif