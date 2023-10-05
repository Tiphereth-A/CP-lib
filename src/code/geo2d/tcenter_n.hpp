#ifndef TIFA_LIBS_GEO2D_TCENTER_N
#define TIFA_LIBS_GEO2D_TCENTER_N

#include "triangle.hpp"

namespace tifa_libs::geo {

// 9-point center (X5)
template <class FP>
constexpr point<FP> center_N(triangle<FP> const &t) { return mid_point(center_O(t), center_H(t)); }

}  // namespace tifa_libs::geo

#endif
