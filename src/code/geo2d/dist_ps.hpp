#ifndef TIFALIBS_GEO2D_DIST_PS
#define TIFALIBS_GEO2D_DIST_PS

#include "dist_pp.hpp"
#include "point_is_in_middle.hpp"
#include "proj.hpp"

namespace tifa_libs::geo {

// the point which is min dist_PP from a point to another point which belongs to a segment
template <class FP>
CEXP point<FP> dist_PS_P(point<FP> CR p, line<FP> CR s) {
  if (s.l == s.r) return s.l;
  if (const point<FP> h = proj(s, p); is_in_middle(s.l, h, s.r)) return h;
  return is_lt(dist_PP(s.l, p), dist_PP(s.r, p)) ? s.l : s.r;
}
// min dist_PP from a point to another point which belongs to a segment
template <class FP>
CEXP FP dist_PS(point<FP> CR p, line<FP> CR s) { return dist_PP(dist_PS_P(p, s), p); }

}  // namespace tifa_libs::geo

#endif