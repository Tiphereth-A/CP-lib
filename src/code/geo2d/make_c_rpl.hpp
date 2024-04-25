#ifndef TIFALIBS_GEO2D_MAKE_C_RPL
#define TIFALIBS_GEO2D_MAKE_C_RPL

#include "ins_cl.hpp"

namespace tifa_libs::geo {

// make circle by radius, a point passed through and a tagante lines
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<circle<FP>>> make_C_rPL(FP r, point<FP> CR p, line<FP> CR l) {
  FP dis = dist_PL(p, l);
  if (is_pos(dis - r * 2)) return {};
  point dir = l.direction();
  dir *= r / dir.norm();
  point dirl = rot90(dir), dirr = rot270(dir);
  if (is_zero(dis)) return {{p + dirl, r}, {p + dirr, r}};
  circle c{p, r};
  if (auto ps = ins_CL(c, {l.l + dirl, l.r + dirl}); !ps.has_value() && !(ps = ins_CL(c, {l.l + dirr, l.r + dirr})).has_value()) return {};
  else return {{ps.value().first, r}, {ps.value().second, r}};
}

}  // namespace tifa_libs::geo

#endif