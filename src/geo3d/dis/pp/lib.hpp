#pragma once

#include "../../ds/p/lib.hpp"

namespace tifa_libs::geo {

template <class FP>
CEXP FP dist3_PP(point3d<FP> CR a, point3d<FP> CR b) NE { return (a - b).norm(); }

}  // namespace tifa_libs::geo
