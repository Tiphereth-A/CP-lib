#ifndef TIFA_LIBS_GEO2D_TCENTER_E
#define TIFA_LIBS_GEO2D_TCENTER_E

#include "triangle.hpp"

namespace tifa_libs::geo {

// excenter of A
template <class FP>
constexpr point<FP> center_EA(triangle<FP> const &t) { return t.trilinears(-1, 1, 1); }
// excenter of B
template <class FP>
constexpr point<FP> center_EB(triangle<FP> const &t) { return t.trilinears(1, -1, 1); }
// excenter of C
template <class FP>
constexpr point<FP> center_EC(triangle<FP> const &t) { return t.trilinears(1, 1, -1); }

}  // namespace tifa_libs::geo

#endif