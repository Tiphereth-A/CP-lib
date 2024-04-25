#ifndef TIFALIBS_GEO2D_TCENTER_I
#define TIFALIBS_GEO2D_TCENTER_I

#include "triangle.hpp"

namespace tifa_libs::geo {

// radius of inscribed circle
template <class FP>
CEXP FP radius_I(triangle<FP> CR t) {
  auto [a, b, c] = t.edges();
  return 2 * t.area() / (a + b + c);
}

// incenter (X1)
template <class FP>
CEXP point<FP> center_I(triangle<FP> CR t) { return t.trilinears(1, 1, 1); }

}  // namespace tifa_libs::geo

#endif