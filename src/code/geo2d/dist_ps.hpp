#ifndef TIFALIBS_GEO2D_DIST_PS
#define TIFALIBS_GEO2D_DIST_PS

#include "dist_pp.hpp"
#include "point_is_in_middle.hpp"
#include "proj.hpp"

namespace tifa_libs::geo {

// min dist_PP from a point to another point which belongs to a segment
template <class FP>
CEXP FP dist_PS(point<FP> CR p, line<FP> CR s) {
  if (s.l == s.r) return dist_PP(s.l, p);
  if (point h = proj(s, p); is_in_middle(s.l, h, s.r)) return dist_PP(p, h);
  return min(dist_PP(s.l, p), dist_PP(s.r, p));
}

}  // namespace tifa_libs::geo

#endif