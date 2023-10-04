#ifndef TIFA_LIBS_GEO2D_CIRCLE
#define TIFA_LIBS_GEO2D_CIRCLE

#include "circle_class.hpp"
#include "line.hpp"
#include "triangle.hpp"
#include "util.hpp"

#include "rel_cc.hpp"
#include "rel_cp.hpp"

namespace tifa_libs::geo2d {

// intersection point of circle and line
// maybe 0, 2 (maybe duplicate)
template <class FP>
vec<point<FP>> ins_CL(circle<FP> const &c, line<FP> const &l1) {
  if (is_ge(std::abs((c.o - l1.l) ^ (l1.r - l1.l) / dist_PP(l1.l, l1.r)), c.r)) return {};
  FP x = (l1.l - c.o) * (l1.r - l1.l), y = l1.direction().norm2(), d = std::max(x * x - y * ((l1.l - c.o).norm2() - c.r * c.r), FP{});
  point m = l1.l - l1.direction() * (x / y), dr = l1.direction() * (std::sqrt(d) / y);
  return {m - dr, m + dr};
}
// intersection point of two circles
//! need to check whether two circles are the same
// maybe 0, 2 (maybe duplicate)
template <class FP>
vec<point<FP>> ins_CC(circle<FP> const &c1, circle<FP> const &c2) {
  assert(!is_eq(c1.o.x, c2.o.x) || !is_eq(c1.o.y, c2.o.y) || !is_eq(c1.r, c2.r));
  auto state = relation_CC(c1, c2);
  if (state == RELCC::lyingin_cc || state == RELCC::lyingout_cc) return {};
  FP d = std::min(dist_PP(c1.o, c2.o), c1.r + c2.r);
  FP y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d), x = std::sqrt(c1.r * c1.r - y * y);
  point dr = (c2.o - c1.o).do_unit();
  point q1 = c1.o + dr * y, q2 = dr.do_rot90() * x;
  return {q1 - q2, q1 + q2};
}
// make circle by 3 point passed through
template <class FP>
constexpr circle<FP> make_C_PPP(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) {
  point o = triangle{p1, p2, p3}.center_O();
  return {o, dist_PP(o, p1)};
}
// make circle by radius and 2 point passed through
// maybe 0, 2 (maybe duplicate)
template <class FP>
vec<circle<FP>> make_C_rPP(FP r, point<FP> const &p1, point<FP> const &p2) {
  vec<point<FP>> ps = ins_CC({p1, r}, {p2, r});
  vec<circle<FP>> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
}
// make circle by radius, a point passed through and a tagante lines
// maybe 0, 2 (maybe duplicate)
template <class FP>
vec<circle<FP>> make_C_rPL(FP r, point<FP> const &p, line<FP> const &l) {
  FP dis = dist_PL(p, l);
  if (is_pos(dis - r * 2)) return {};
  point dir = l.direction();
  dir *= r / dir.abs();
  point dirl = rot90(dir), dirr = rot270(dir);
  if (is_zero(dis)) return {{p + dirl, r}, {p + dirr, r}};
  circle c{p, r};
  vec<point<FP>> ps = ins_CL(c, {l.l + dirl, l.r + dirl});
  if (ps.size() == 0) ps = ins_CL(c, {l.l + dirr, l.r + dirr});
  vec<circle<FP>> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
}
// make circle by radius and 2 tagante lines
// maybe 0, 4
template <class FP>
vec<circle<FP>> make_C_rLL(FP r, line<FP> const &l1, line<FP> const &l2) {
  if (is_parallel(l1, l2)) return {};
  point<FP> dir1 = l1.direction(), dir2 = l2.direction();
  dir1 *= r / dir1.abs();
  dir2 *= r / dir2.abs();
  point<FP> dirl1 = rot90(dir1), dirr1 = rot270(dir1), dirl2 = rot90(dir2), dirr2 = rot270(dir2);
  line<FP> u1 = {l1.l + dirl1, l1.r + dirl1},
           u2 = {l1.l + dirr1, l1.r + dirr1},
           v1 = {l2.l + dirl2, l2.r + dirl2},
           v2 = {l2.l + dirr2, l2.r + dirr2};
  return {{ins_LL(u1, v1), r}, {ins_LL(u1, v2), r}, {ins_LL(u2, v1), r}, {ins_LL(u2, v2), r}};
}
// make circle by radius and 2 external tagante circle
// maybe 0, 2 (maybe duplicate)
template <class FP>
vec<circle<FP>> make_C_rCC_ex(FP r, circle<FP> const &c1, circle<FP> const &c2) {
  if (relation_CC(c1, c2) == RELCC::lyingin_cc) return {};
  vec<point<FP>> ps = ins_CC({c1.o, c1.r + r}, {c2.o, c2.r + r});
  vec<circle<FP>> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
}

// geometry inverse of a point
template <class FP>
constexpr point<FP> inv_P2P(circle<FP> const &c, point<FP> const &p) {
  point v = p - c.o;
  return c.o + v * (c.r * c.r / v.norm2());
}
// geometry inverse of a circle which DOES NOT pass through the inversion center
template <class FP>
constexpr circle<FP> inv_C2C(circle<FP> const &c, circle<FP> const &c2) {
  point v = (c2.o - c.o).do_unit();
  point p1 = inv_P2P(c, c2.o + v * c2.r), p2 = inv_P2P(c, c2.o - v * c2.r);
  return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}
// geometry inverse of a circle which pass through the inversion center
template <class FP>
constexpr line<FP> inv_C2L(circle<FP> const &c, circle<FP> const &c2) {
  point v = (c2.o - c.o).do_rot90();
  return {inv_P2P(c, c2.o + v), inv_P2P(c, c2.o - v)};
}
// geometry inverse of a line
template <class FP>
constexpr circle<FP> inv_L2C(circle<FP> const &c, line<FP> const &l) {
  point p1 = inv_P2P(c, l.l), p2 = inv_P2P(c, l.r);
  return make_C_PPP(p1, p2, c.o);
}

// tagante points of point to circle // maybe 0, 2 (maybe duplicate)
template <class FP>
vec<point<FP>> tan_CP(circle<FP> const &c, point<FP> const &p) {
  point v = p - c.o;
  FP x = v.norm2(), d = x - c.r * c.r;
  if (is_neg(d)) return {};
  point q1 = c.o + v * (c.r * c.r / x);
  point q2 = v.do_rot90() * (c.r * std::sqrt(d) / x);
  // counter clock-wise
  return {q1 - q2, q1 + q2};
}
// external tagante lines of 2 circles // maybe 0, 2 (maybe duplicate)
template <class FP>
vec<line<FP>> extan_CC(circle<FP> const &c1, circle<FP> const &c2) {
  if (is_eq(c1.o.x, c2.o.x) && is_eq(c1.o.y, c2.o.y)) return {};
  vec<line<FP>> ret;
  if (is_eq(c1.r, c2.r)) {
    point dr = (c2.o - c1.o).do_unit().do_rot90() * c1.r;
    ret.emplace_back(c1.o + dr, c2.o + dr);
    ret.emplace_back(c1.o - dr, c2.o - dr);
  } else {
    point p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
    vec<point<FP>> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
    // c1 counter-clock wise
    for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i) ret.emplace_back(ps[i], qs[i]);
  }
  return ret;
}
// internal tagante lines of 2 disjoint circles // maybe 0, 2 (maybe duplicate)
template <class FP>
vec<line<FP>> intan_CC(circle<FP> const &c1, circle<FP> const &c2) {
  if (is_eq(c1.o.x, c2.o.x) && is_eq(c1.o.y, c2.o.y)) return {};
  vec<line<FP>> ret;
  point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
  vec<point<FP>> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  // c1 counter-clock wise
  for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i) ret.emplace_back(ps[i], qs[i]);
  return ret;
}

// area of intersection of circle and triangle
//! WITH DIRECTION, sgn is cross(c.o, p1, p2)
//! the center ot circle is also a endpoint of triangle
template <class FP>
FP sarea_CT(circle<FP> const &c, point<FP> const &p1, point<FP> const &p2) {
  if (is_zero(cross(c.o, p1, p2))) return FP{};
  vec<point<FP>> is = ins_CL(c, {p1, p2});
  if (is.empty()) return c.area(ang_PP(p1 - c.o, p2 - c.o));
  bool b1 = is_ge(dist_PP(p1, c.o), c.r), b2 = is_ge(dist_PP(p2, c.o), c.r);
  if (b1 && b2) {
    FP res = c.area(ang_PP(p1 - c.o, p2 - c.o));
    if (!is_pos(dot(is[0], p1, p2))) res -= c.crown_area(ang_PP(is[0] - c.o, is[1] - c.o));
    return res;
  }
  if (b1) return c.area(ang_PP(p1 - c.o, is[0] - c.o)) + cross(c.o, is[0], p2) / 2;
  if (b2) return c.area(ang_PP(is[1] - c.o, p2 - c.o)) + cross(c.o, p1, is[1]) / 2;
  return cross(c.o, p1, p2) / 2;
}
template <class FP>
constexpr FP area_CC(circle<FP> const &lhs, circle<FP> const &rhs) {
  auto relation = relation_CC(lhs, rhs);
  if (relation == RELCC::lyingout_cc || relation == RELCC::touchex_cc) return FP{};
  if (relation == RELCC::lyingin_cc || relation == RELCC::touchin_cc) return std::min(
    lhs.area(), rhs.area());
  FP d = dist_PP(lhs.o, rhs.o);
  return lhs.crown_area(std::acos((lhs.r * lhs.r - rhs.r * rhs.r + d * d) / (2 * lhs.r * d)) * 2) + rhs.crown_area(std::acos((rhs.r * rhs.r - lhs.r * lhs.r + d * d) / (2 * rhs.r * d)) * 2);
}

// min coverage circle of a set of points
//! accuracy maybe reduced without shuffling `vp` first
template <class FP>
circle<FP> min_cover_C(vec<point<FP>> const &vp) {
  circle ret{vp.front(), 0};
  size_t sz = vp.size();
  for (size_t i = 1; i < sz; ++i) {
    if (relation_CP(ret, vp[i]) != RELCP::outside_cp) continue;
    ret = circle{vp[i], 0};
    for (size_t j = 0; j < i; ++j) {
      if (relation_CP(ret, vp[j]) != RELCP::outside_cp) continue;
      ret = circle{mid_point(vp[i], vp[j]), dist_PP(vp[i], vp[j]) / 2};
      for (size_t k = 0; k < j; ++k) {
        if (relation_CP(ret, vp[k]) != RELCP::outside_cp) continue;
        ret = make_C_PPP(vp[i], vp[j], vp[k]);
      }
    }
  }
  return ret;
}

}  // namespace tifa_libs::geo2d

#endif