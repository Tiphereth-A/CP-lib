#ifndef TIFA_LIBS_GEO2D_AREA_TRIAEDGES
#define TIFA_LIBS_GEO2D_AREA_TRIAEDGES

#include "../util/util.hpp"

namespace tifa_libs::geo2d {

// calculate area of triangle by the length of 3 edges
// numerical stability improved
template <class FP>
constexpr FP area_T_abc(FP a, FP b, FP c) { return std::sqrt((a + (b + c)) * (c - (a - b)) * (c + (a - b)) * (a + (b - c))) / 4; }

}  // namespace tifa_libs::geo2d

#endif