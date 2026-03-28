#pragma once

#include "../../ds/pl/lib.hpp"

namespace tifa_libs {

// relation between plane and point3d
// clang-format off
enum class RELPLP : u8 { above, in, below };
// clang-format on

template <class FP>
CEXP RELPLP relation_PlP(planev<FP> CR pl, point3d<FP> CR p) NE {
  const FP d = (p - *pl.u) * pl.normal();
  if (is_pos(d)) return RELPLP::above;
  if (is_neg(d)) return RELPLP::below;
  return RELPLP::in;
}

}  // namespace tifa_libs
