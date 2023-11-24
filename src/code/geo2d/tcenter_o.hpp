#ifndef TIFA_LIBS_GEO2D_TCENTER_O
#define TIFA_LIBS_GEO2D_TCENTER_O

#include "triangle.hpp"

namespace tifa_libs::geo {

// radius of circumscribed circle
template <class FP>
constexpr FP radius_O(triangle<FP> const &t) { return dist_PP(t.B, t.C) / std::sin(std::abs(ang_PP(t.B - t.A, t.C - t.A))) / 2; }

// circumcenter (X3)
template <class FP>
constexpr point<FP> center_O(triangle<FP> const &t) {
  auto [A, B, C] = t.angles();
  return t.trilinears(std::cos(A), std::cos(B), std::cos(C));
}

}  // namespace tifa_libs::geo

#endif