#ifndef TIFALIBS_GEO2D_DIST_PL
#define TIFALIBS_GEO2D_DIST_PL

#include "proj.hpp"

namespace tifa_libs::geo {

// min dist_PP from a point to a line
template <class FP>
CEXP FP dist_PL(point<FP> CR p, line<FP> CR s) NE { return s.l == s.r ? dist_PP(s.l, p) : dist_PP(p, proj(s, p)); }

}  // namespace tifa_libs::geo

#endif