#ifndef TIFA_LIBS_GEO2D_TCENTER_X
#define TIFA_LIBS_GEO2D_TCENTER_X

#include "triangle.hpp"

namespace tifa_libs::geo {

// fermat center (X13)
template <class FP>
point<FP> center_X(triangle<FP> const &t) {
  auto [A, B, C] = t.angles();
  return t.trilinears(1 / std::sin(A + PI<FP> / 3), 1 / std::sin(B + PI<FP> / 3), 1 / std::sin(C + PI<FP> / 3));
}

}  // namespace tifa_libs::geo

#endif