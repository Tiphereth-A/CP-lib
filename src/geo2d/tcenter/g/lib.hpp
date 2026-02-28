#ifndef TIFALIBS_GEO2D_TCENTER_G_LIB
#define TIFALIBS_GEO2D_TCENTER_G_LIB

#include "../../ds/t/lib.hpp"

namespace tifa_libs::geo {

// centroid (X2)
template <class FP>
CEXP point<FP> center_G(triangle<FP> CR t) NE { return t.barycentrics(1, 1, 1); }

}  // namespace tifa_libs::geo

#endif