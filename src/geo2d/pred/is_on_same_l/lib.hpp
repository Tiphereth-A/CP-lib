#pragma once

#include "../../cross/lib.hpp"
#include "../../ds/p/lib.hpp"

namespace tifa_libs {

template <class FP>
CEXP bool is_on_same_L(point<FP> CR p1, point<FP> CR p2, point<FP> CR p3) NE { return is_zero(cross(p1, p2, p3)); }

}  // namespace tifa_libs
