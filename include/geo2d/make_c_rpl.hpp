#ifndef TIFALIBS_GEO2D_MAKE_C_RPL
#define TIFALIBS_GEO2D_MAKE_C_RPL

#include "dist_pl.hpp"
#include "ins_cl.hpp"

namespace tifa_libs::geo {

// make circle by radius, a point passed through and a tagante lines
// maybe duplicate
template <class FP>
CEXP auto make_C_rPL(FP r, point<FP> CR p, line<FP> CR l) NE {
  std::optional<ptt<circle<FP>>> ret;
  FP dis = dist_PL(p, l);
  if (is_pos(dis - r * 2)) return ret;
  point dir = l.direction();
  dir *= r / dir.norm();
  const point dirl = rot90(dir), dirr = rot270(dir);
  if (is_zero(dis)) {
    ret.emplace(circle{p + dirl, r}, circle{p + dirr, r});
    return ret;
  }
  const circle c{p, r};
  auto ps = ins_CL(c, {l.l + dirl, l.r + dirl});
  if (!ps && !(ps = ins_CL(c, {l.l + dirr, l.r + dirr}))) return ret;
  ret.emplace(circle{ps->first, r}, circle{ps->second, r});
  return ret;
}

}  // namespace tifa_libs::geo

#endif