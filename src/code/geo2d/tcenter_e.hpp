#ifndef TIFALIBS_GEO2D_TCENTER_E
#define TIFALIBS_GEO2D_TCENTER_E

#include "triangle.hpp"

namespace tifa_libs::geo {

// excenter of A
template <class FP>
CEXP point<FP> center_EA(triangle<FP> CR t) { return t.trilinears(-1, 1, 1); }
// excenter of B
template <class FP>
CEXP point<FP> center_EB(triangle<FP> CR t) { return t.trilinears(1, -1, 1); }
// excenter of C
template <class FP>
CEXP point<FP> center_EC(triangle<FP> CR t) { return t.trilinears(1, 1, -1); }

}  // namespace tifa_libs::geo

#endif