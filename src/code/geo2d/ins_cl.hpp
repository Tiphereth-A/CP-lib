#ifndef TIFALIBS_GEO2D_INS_CL
#define TIFALIBS_GEO2D_INS_CL

#include "circle.hpp"
#include "dist_pp.hpp"
#include "line.hpp"

namespace tifa_libs::geo {

// intersection point of circle and line
// maybe duplicate
template <class FP>
CEXP std::optional<ptt<point<FP>>> ins_CL(circle<FP> CR c, line<FP> CR l) {
  if (is_gt(abs((c.o - l.l) ^ (l.r - l.l) / dist_PP(l.l, l.r)), c.r)) return {};
  FP x = (l.l - c.o) * (l.r - l.l), y = l.direction().norm2(), d = max(x * x - y * ((l.l - c.o).norm2() - c.r * c.r), FP{});
  point m = l.l - l.direction() * (x / y), dr = l.direction() * (std::sqrt(d) / y);
  return ptt<point<FP>>{m - dr, m + dr};
}

}  // namespace tifa_libs::geo

#endif