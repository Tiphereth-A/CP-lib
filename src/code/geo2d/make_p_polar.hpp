#ifndef TIFALIBS_GEO2D_MAKE_P_POLAR
#define TIFALIBS_GEO2D_MAKE_P_POLAR

#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP point<FP> make_P_polar(FP r, FP theta) { return point{r * std::cos(theta), r * std::sin(theta)}; }

}  // namespace tifa_libs::geo

#endif