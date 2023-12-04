#ifndef TIFALIBS_GEO2D_TCENTER_N
#define TIFALIBS_GEO2D_TCENTER_N

#include "triangle.hpp"

namespace tifa_libs::geo {

// 9-point center (X5)
template <class FP>
constexpr point<FP> center_N(triangle<FP> const &t) {
  auto [A, B, C] = t.angles();
  return t.trilinears(std::cos(B - C), std::cos(C - A), std::cos(A - B));
}

}  // namespace tifa_libs::geo

#endif