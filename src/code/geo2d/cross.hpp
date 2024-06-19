#ifndef TIFALIBS_GEO2D_CROSS
#define TIFALIBS_GEO2D_CROSS

#include "../util/fp_comp.hpp"

namespace tifa_libs::geo {

template <class P>
CEXP auto cross(P CR o, P CR a, P CR b) { return (a - o) ^ (b - o); }
template <class P>
requires std::floating_point<typename P::FP_t>
CEXP auto cross_unit(P CR o, P CR a, P CR b) { return (a - o).do_unit() ^ (b - o).do_unit(); }
template <class P>
requires std::floating_point<typename P::FP_t>
CEXP int sgn_cross(P CR o, P CR a, P CR b) { return sgn(cross_unit(o, a, b)); }
template <class P>
CEXP int sgn_cross(P CR o, P CR a, P CR b) { return sgn(cross(o, a, b)); }

}  // namespace tifa_libs::geo

#endif