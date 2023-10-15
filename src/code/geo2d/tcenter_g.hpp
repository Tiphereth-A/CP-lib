#ifndef TIFA_LIBS_GEO2D_TCENTER_G
#define TIFA_LIBS_GEO2D_TCENTER_G

#include "triangle.hpp"

namespace tifa_libs::geo {

// centroid (X2)
template <class FP>
constexpr point<FP> center_G(triangle<FP> const &t) { return t.average_w(1, 1, 1); }

}  // namespace tifa_libs::geo

#endif