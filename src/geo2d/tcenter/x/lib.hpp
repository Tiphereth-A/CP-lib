#pragma once

#include "../../ds/t/lib.hpp"

namespace tifa_libs {

// fermat center (X13)
template <class FP>
CEXP point<FP> center_X(triangle<FP> CR t) NE {
  auto [A, B, C] = t.angles();
  return t.trilinears(1 / std::sin(A + pi_v<FP> / 3), 1 / std::sin(B + pi_v<FP> / 3), 1 / std::sin(C + pi_v<FP> / 3));
}

}  // namespace tifa_libs
