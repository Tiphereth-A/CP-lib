#pragma once

#include "../../util/util/lib.hpp"

namespace tifa_libs::geo {

template <class P>
CEXP TPN P::FP_t dot(P CR o, P CR a, P CR b) NE { return (a - o) * (b - o); }
template <class P>
CEXP int sgn_dot(P CR o, P CR a, P CR b) NE { return sgn(dot(o, a, b)); }

}  // namespace tifa_libs::geo
