#ifndef TIFALIBS_GEO2D_TCENTER_I
#define TIFALIBS_GEO2D_TCENTER_I

#include "triangle.hpp"

namespace tifa_libs::geo {

// radius of inscribed circle
template <class FP>
constexpr FP radius_I(triangle<FP> const &t) {
  auto [a, b, c] = t.edges();
  return 2 * t.area() / (a + b + c);
}

// incenter (X1)
template <class FP>
constexpr point<FP> center_I(triangle<FP> const &t) { return t.trilinears(1, 1, 1); }

}  // namespace tifa_libs::geo

#endif