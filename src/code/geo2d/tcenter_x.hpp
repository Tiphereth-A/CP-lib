#ifndef TIFA_LIBS_GEO2D_TCENTER_X
#define TIFA_LIBS_GEO2D_TCENTER_X

#include "tcenter_g.hpp"
#include "tcenter_i.hpp"
#include "tcenter_o.hpp"

namespace tifa_libs::geo {

// fermat center (X13)
template <class FP>
point<FP> center_X(triangle<FP> const &t) {
  FP s3 = std::sqrt(FP{3}), r = radius_I(t), R = radius_O(t), s = ((t.A - t.B).norm() + (t.B - t.C).norm() + (t.C - t.A).norm()) / 2;
  return center_I(t) * (s3 * (r * r + 2 * r * R + s * s)) + center_O(t) * (-6 * r * (s3 * R - 2 * s)) + center_G(t) * (-2 * r * (s3 * r + 3 * s));
}

}  // namespace tifa_libs::geo

#endif