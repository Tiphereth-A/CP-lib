#ifndef TIFALIBS_GEO2D_DIST_SS
#define TIFALIBS_GEO2D_DIST_SS

#include "dist_ps.hpp"
#include "is_ins_ss.hpp"

namespace tifa_libs::geo {

// dist_PP of two segments
template <class FP>
CEXP FP dist_SS(line<FP> CR s1, line<FP> CR s2) { return is_ins_SS(s1, s2) ? 0 : min({dist_PS(s1.l, s2), dist_PS(s1.r, s2), dist_PS(s2.l, s1), dist_PS(s2.r, s1)}); }

}  // namespace tifa_libs::geo

#endif