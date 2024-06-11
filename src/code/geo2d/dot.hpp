#ifndef TIFALIBS_GEO2D_DOT
#define TIFALIBS_GEO2D_DOT

#include "../util/util.hpp"

namespace tifa_libs::geo {

template <class P>
CEXP typename P::FP_t dot(P CR o, P CR a, P CR b) { return (a - o) * (b - o); }
template <class P>
CEXP int sgn_dot(P CR o, P CR a, P CR b) { return sgn(dot(o, a, b)); }

}  // namespace tifa_libs::geo

#endif