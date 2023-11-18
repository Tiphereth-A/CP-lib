#ifndef TIFA_LIBS_GEO2D_DIST_PL
#define TIFA_LIBS_GEO2D_DIST_PL

#include "proj.hpp"

namespace tifa_libs::geo {

// min dist_PP from a point to a line
template <class FP>
constexpr FP dist_PL(point<FP> const &p, line<FP> const &s) { return s.l == s.r ? dist_PP(s.l, p) : dist_PP(p, proj(s, p)); }

}  // namespace tifa_libs::geo

#endif