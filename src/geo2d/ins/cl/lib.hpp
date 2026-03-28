#pragma once

#include "../../dis/pp/lib.hpp"
#include "../../ds/c/lib.hpp"
#include "../../ds/l/lib.hpp"

namespace tifa_libs {

// intersection point of circle and line
// maybe duplicate
template <class FP>
CEXP auto ins_CL(circle<FP> CR c, line<FP> CR l) NE {
  std::optional<ptt<point<FP>>> ret;
  if (is_gt(abs((c.o - l.l) ^ (l.r - l.l) / dist_PP(l.l, l.r)), c.r)) return ret;
  const FP x = (l.l - c.o) * (l.r - l.l),
           y = l.direction().norm2(),
           d = max(x * x - y * ((l.l - c.o).norm2() - c.r * c.r), FP{});
  const point m = l.l - l.direction() * (x / y), dr = l.direction() * (std::sqrt(d) / y);
  ret.emplace(m - dr, m + dr);
  return ret;
}

}  // namespace tifa_libs
