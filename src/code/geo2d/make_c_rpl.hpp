#ifndef TIFA_LIBS_GEO2D_MAKE_C_RPL
#define TIFA_LIBS_GEO2D_MAKE_C_RPL

#include "ins_cl.hpp"

namespace tifa_libs::geo2d {

// make circle by radius, a point passed through and a tagante lines
// maybe duplicate
template <class FP>
std::optional<ptt<circle<FP>>> make_C_rPL(FP r, point<FP> const &p, line<FP> const &l) {
  FP dis = dist_PL(p, l);
  if (is_pos(dis - r * 2)) return {};
  point dir = l.direction();
  dir *= r / dir.norm();
  point dirl = rot90(dir), dirr = rot270(dir);
  if (is_zero(dis)) return {{p + dirl, r}, {p + dirr, r}};
  circle c{p, r};
  auto ps = ins_CL(c, {l.l + dirl, l.r + dirl});
  if (!ps.has_value()) ps = ins_CL(c, {l.l + dirr, l.r + dirr});
  if (!ps.has_value()) return {};
  return {{ps.value().first, r}, {ps.value().second, r}};
}

}  // namespace tifa_libs::geo2d

#endif