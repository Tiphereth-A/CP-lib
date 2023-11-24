#ifndef TIFA_LIBS_GEO2D_TCENTER_H
#define TIFA_LIBS_GEO2D_TCENTER_H

#include "triangle.hpp"

namespace tifa_libs::geo {

// orthocenter (X4)
template <class FP>
constexpr point<FP> center_H(triangle<FP> const &t) {
  auto [A, B, C] = t.angles();
  return t.trilinears(1 / std::cos(A), 1 / std::cos(B), 1 / std::cos(C));
}

}  // namespace tifa_libs::geo

#endif