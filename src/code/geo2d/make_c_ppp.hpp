#ifndef TIFALIBS_GEO2D_MAKE_C_PPP
#define TIFALIBS_GEO2D_MAKE_C_PPP

#include "circle.hpp"
#include "tcenter_o.hpp"

namespace tifa_libs::geo {

// make circle by 3 point passed through
template <class FP>
CEXP circle<FP> make_C_PPP(point<FP> CR p1, point<FP> CR p2, point<FP> CR p3) {
  point o = center_O(triangle{p1, p2, p3});
  return {o, dist_PP(o, p1)};
}

}  // namespace tifa_libs::geo

#endif