#ifndef TIFALIBS_GEO2D_TCENTER_X
#define TIFALIBS_GEO2D_TCENTER_X

#include "triangle.hpp"

namespace tifa_libs::geo {

// fermat center (X13)
template <class FP>
CEXP point<FP> center_X(triangle<FP> CR t) {
  auto [A, B, C] = t.angles();
  return t.trilinears(1 / std::sin(A + std::numbers::pi_v<FP> / 3), 1 / std::sin(B + std::numbers::pi_v<FP> / 3), 1 / std::sin(C + std::numbers::pi_v<FP> / 3));
}

}  // namespace tifa_libs::geo

#endif