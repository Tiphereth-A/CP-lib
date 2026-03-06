#pragma once

#include "../../../geo2d/cross/lib.hpp"
#include "../../ds/l/lib.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP dist3_PL(point3d<FP> CR p, line3d<FP> CR l) NE { return cross(l.l, l.r, p).norm() / (l.r - l.l).norm(); }

}  // namespace tifa_libs::geo
