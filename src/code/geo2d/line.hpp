#ifndef TIFA_LIBS_GEO2D_LINE
#define TIFA_LIBS_GEO2D_LINE

#include "line_class.hpp"

namespace tifa_libs::geo2d {

// judge if two lines are intersected or not
template <class FP>
constexpr bool is_ins_LL(line<FP> const &l1, line<FP> const &l2) { return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r)); }
// intersection point of two lines
template <class FP>
constexpr point<FP> ins_LL(line<FP> const &l1, line<FP> const &l2) {
  FP a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}

// judge if two segments are intersected or not
//! containing endpoints
template <class FP>
constexpr bool is_ins_SS(line<FP> const &l1, line<FP> const &l2) { return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) && is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) && sgn_cross(l1.l, l1.r, l2.l) * sgn_cross(l1.l, l1.r, l2.r) <= 0 && sgn_cross(l2.l, l2.r, l1.l) * sgn_cross(l2.l, l2.r, l1.r) <= 0; }
// judge if two segments are intersected or not
//! NOT containing endpoints
template <class FP>
constexpr bool is_ins_SS_strict(line<FP> const &s1, line<FP> const &s2) { return sgn_cross(s1.l, s1.r, s2.l) * sgn_cross(s1.l, s1.r, s2.r) < 0 && sgn_cross(s2.l, s2.r, s1.l) * sgn_cross(s2.l, s2.r, s1.r) < 0; }

// projection to a line
template <class FP>
constexpr point<FP> proj(line<FP> const &l1, point<FP> const &p) {
  point dir = l1.direction();
  return l1.l + dir * (dir * (p - l1.l) / dir.norm2());
}
// reflection about a line
template <class FP>
constexpr point<FP> reflect(line<FP> const &l1, point<FP> const &p) { return proj(l1, p) * 2 - p; }
template <class FP>
constexpr bool is_on_same_L(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return is_zero(cross(p1, p2, p3)); }

//! containing endpoints
template <class FP>
constexpr bool is_on_S(line<FP> const &s1, point<FP> const &p) { return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r); }
//! NOT containing endpoints
template <class FP>
constexpr bool is_on_S_strict(line<FP> const &s1, point<FP> const &p) { return sgn_cross(s1.l, s1.r, p) == 0 && sgn((p - s1.l) * (s1.l - s1.r)) * sgn((p - s1.r) * (s1.l - s1.r)) < 0; }

// min dist_PP from a point to a line
template <class FP>
constexpr FP dist_PL(point<FP> const &p, line<FP> const &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  return dist_PP(p, proj(s1, p));
}
// min dist_PP from a point to another point which belongs to a segment
template <class FP>
constexpr FP dist_PS(point<FP> const &p, line<FP> const &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  point h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
// dist_PP of two segments
template <class FP>
constexpr FP dist_SS(line<FP> const &s1, line<FP> const &s2) {
  if (is_ins_SS(s1, s2)) return 0;
  return std::min({dist_PS(s1.l, s2), dist_PS(s1.r, s2), dist_PS(s2.l, s1), dist_PS(s2.r, s1)});
}

}  // namespace tifa_libs::geo2d

#endif