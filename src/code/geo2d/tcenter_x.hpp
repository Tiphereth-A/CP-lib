#ifndef TIFALIBS_GEO2D_TCENTER_X
#define TIFALIBS_GEO2D_TCENTER_X

#include "triangle.hpp"

namespace tifa_libs::geo {

// fermat center (X13)
template <class FP>
constexpr point<FP> center_X(triangle<FP> const &t) {
  auto [A, B, C] = t.angles();
  return t.trilinears(1 / std::sin(A + pi_v<FP> / 3), 1 / std::sin(B + pi_v<FP> / 3), 1 / std::sin(C + pi_v<FP> / 3));
}

}  // namespace tifa_libs::geo

#endif