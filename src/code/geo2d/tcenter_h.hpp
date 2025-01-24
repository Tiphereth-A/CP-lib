#ifndef TIFALIBS_GEO2D_TCENTER_H
#define TIFALIBS_GEO2D_TCENTER_H

#include "triangle.hpp"

namespace tifa_libs::geo {

// orthocenter (X4)
template <class FP>
CEXP point<FP> center_H(triangle<FP> CR t) NE {
  auto [A, B, C] = t.angles();
  return t.trilinears(1 / std::cos(A), 1 / std::cos(B), 1 / std::cos(C));
}

}  // namespace tifa_libs::geo

#endif