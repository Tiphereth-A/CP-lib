#ifndef TIFA_LIBS_GEO2D_INS_CL
#define TIFA_LIBS_GEO2D_INS_CL

#include "circle.hpp"
#include "dist_pp.hpp"
#include "line.hpp"

namespace tifa_libs::geo2d {

// intersection point of circle and line
// maybe duplicate
template <class FP>
std::optional<ptt<point<FP>>> ins_CL(circle<FP> const &c, line<FP> const &l1) {
  if (is_ge(std::abs((c.o - l1.l) ^ (l1.r - l1.l) / dist_PP(l1.l, l1.r)), c.r)) return {};
  FP x = (l1.l - c.o) * (l1.r - l1.l), y = l1.direction().norm2(), d = std::max(x * x - y * ((l1.l - c.o).norm2() - c.r * c.r), FP{});
  point m = l1.l - l1.direction() * (x / y), dr = l1.direction() * (std::sqrt(d) / y);
  return ptt<point<FP>>{m - dr, m + dr};
}

}  // namespace tifa_libs::geo2d

#endif