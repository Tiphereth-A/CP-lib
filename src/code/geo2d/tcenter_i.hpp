#ifndef TIFA_LIBS_GEO2D_TCENTER_I
#define TIFA_LIBS_GEO2D_TCENTER_I

#include "triangle.hpp"

namespace tifa_libs::geo2d {

// radius of inscribed circle
template <class FP>
constexpr FP radius_I(triangle<FP> const &t) {
  FP ab = dist_PP(t.A, t.B), bc = dist_PP(t.B, t.C), ca = dist_PP(t.C, t.A);
  return 2 * t.area() / (ab + bc + ca);
}

// incenter (X1)
template <class FP>
constexpr point<FP> center_I(triangle<FP> const &t) { return t.average_w((t.B - t.C).norm(), (t.C - t.A).norm(), (t.A - t.B).norm()); }

}  // namespace tifa_libs::geo2d

#endif
