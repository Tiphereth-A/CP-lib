#pragma once

#include "../../ds/c/lib.hpp"
#include "../../ds/l/lib.hpp"

namespace tifa_libs {

// relation between circle and segment/line
// clang-format off
enum class RELCS : u8 { otherwise, tagante, intersect };
// clang-format on

template <class FP>
CEXP RELCS relation_CS(circle<FP> CR c, line<FP> CR s) NE {
  const FP d = dist_PL(c.o, s);
  if (is_lt(d, c.r)) return RELCS::intersect;
  if (is_eq(d, c.r)) return RELCS::tagante;
  return RELCS::otherwise;
}

}  // namespace tifa_libs
