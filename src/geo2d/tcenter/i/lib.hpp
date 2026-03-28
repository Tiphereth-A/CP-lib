#pragma once

#include "../../ds/t/lib.hpp"

namespace tifa_libs {

// radius of inscribed circle
template <class FP>
CEXP FP radius_I(triangle<FP> CR t) NE {
  auto [a, b, c] = t.edges();
  return 2 * t.area() / (a + b + c);
}
// incenter (X1)
template <class FP>
CEXP point<FP> center_I(triangle<FP> CR t) NE { return t.trilinears(1, 1, 1); }

}  // namespace tifa_libs
