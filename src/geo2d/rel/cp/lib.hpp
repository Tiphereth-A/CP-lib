#pragma once

#include "../../dis/pp_p/lib.hpp"
#include "../../ds/c/lib.hpp"

namespace tifa_libs::geo {

// relation between circle and point
// clang-format off
enum class RELCP : u8 { outside, onborder, inside };
// clang-format on

template <class FP>
CEXP RELCP relation_CP(circle<FP> CR c, point<FP> CR p) NE {
  const auto _ = comp_distp(c.o, p, c.r);
  if (_ < 0) return RELCP::inside;
  if (_ == 0) return RELCP::onborder;
  return RELCP::outside;
}

}  // namespace tifa_libs::geo
