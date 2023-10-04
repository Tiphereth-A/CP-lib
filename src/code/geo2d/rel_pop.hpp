#ifndef TIFA_LIBS_GEO2D_REL_POP
#define TIFA_LIBS_GEO2D_REL_POP

#include "cvh_class.hpp"

namespace tifa_libs::geo2d {

// relation between polygon/convex hull and point
enum RELA_PoP {
  outside_pop,
  onborder_pop,
  onendpoint_pop,
  inside_pop
};

template <class FP>
RELA_PoP relation_PoP(polygon<FP> const &poly, point<FP> const &p) {
  for (auto &&now : poly.vs)
    if (now == p) return RELA_PoP::onendpoint_pop;
  bool result = false;
  for (size_t i = 0; i < poly.vs.size(); ++i) {
    point now_p = poly.vs[i], next_p = poly.vs[poly.next(i)];
    if (is_on_S({now_p, next_p}, p)) return RELA_PoP::onborder_pop;
    if (!is_ge(now_p.y, next_p.y)) std::swap(now_p, next_p);
    if (is_ge(p.y, now_p.y) || !is_ge(p.y, next_p.y)) continue;
    result ^= sgn_cross(p, now_p, next_p) > 0;
  }
  return result ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
}

template <class FP>
RELA_PoP relation_CvhP(cvh<FP> const &cvh, point<FP> const &p) {
  for (auto &&now : cvh.vs)
    if (now == p) return RELA_PoP::onendpoint_pop;
  size_t sz = cvh.vs.size();
  for (size_t i = 0; i < sz; ++i)
    if (is_on_S({cvh.vs[i], cvh.vs[cvh.next(i)]}, p)) return RELA_PoP::onborder_pop;
  if (sz < 3) return RELA_PoP::outside_pop;
  if (is_pos(cross(cvh.vs.front(), p, cvh.vs[1])) || is_pos(cross(cvh.vs.front(), cvh.vs.back(), p))) return RELA_PoP::outside_pop;
  auto it = std::lower_bound(cvh.vs.begin() + 1, cvh.vs.end(), p, [&](point<FP> const &lhs, point<FP> const &rhs) { return is_pos(cross(cvh.vs.front(), lhs, rhs)); }) - 1;
  auto next_it = cvh.next(it);
  auto res = sgn_cross(p, *it, *next_it);
  if (res) return ~res ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
  return !res && !is_pos(dot(p, *it, *next_it)) ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
}

}  // namespace tifa_libs::geo2d

#endif