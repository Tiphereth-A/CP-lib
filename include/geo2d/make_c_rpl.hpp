#ifndef TIFALIBS_GEO2D_MAKE_C_RPL
#define TIFALIBS_GEO2D_MAKE_C_RPL

#include "dist_pl.hpp"
#include "ins_cl.hpp"

namespace tifa_libs::geo {

// make circle by radius, a point passed through and a tagante lines
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<circle<FP>>> make_C_rPL(FP r, point<FP> CR p, line<FP> CR l) NE {
  FP dis = dist_PL(p, l);
  if (is_pos(dis - r * 2)) return {};
  point dir = l.direction();
  dir *= r / dir.norm();
  const point dirl = rot90(dir), dirr = rot270(dir);
  if (is_zero(dis)) return ptt<circle<FP>>{{p + dirl, r}, {p + dirr, r}};
  const circle c{p, r};
  auto ps = ins_CL(c, {l.l + dirl, l.r + dirl});
  if (!ps.has_value() && !(ps = ins_CL(c, {l.l + dirr, l.r + dirr})).has_value()) return {};
  return ptt<circle<FP>>{{ps.value().first, r}, {ps.value().second, r}};
}

}  // namespace tifa_libs::geo

#endif