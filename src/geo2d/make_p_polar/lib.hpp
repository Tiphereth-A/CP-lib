#pragma once

#include "../ds/p/lib.hpp"

namespace tifa_libs {

template <class FP>
CEXP point<FP> make_P_polar(FP r, FP theta) NE { return point{r * std::cos(theta), r * std::sin(theta)}; }

}  // namespace tifa_libs
