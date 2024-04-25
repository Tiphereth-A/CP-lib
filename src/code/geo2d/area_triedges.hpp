#ifndef TIFALIBS_GEO2D_AREA_TRIAEDGES
#define TIFALIBS_GEO2D_AREA_TRIAEDGES

#include "../util/util.hpp"

namespace tifa_libs::geo {

// calculate area of triangle by the length of 3 edges
// numerical stability improved
template <class FP>
CEXP FP area_T_abc(FP a, FP b, FP c) {
  if (a < b) swap(a, b);
  if (a < c) swap(a, c);
  if (b < c) swap(b, c);
  return std::sqrt(a + (b + c)) * std::sqrt(c - (a - b)) * std::sqrt(c + (a - b)) * std::sqrt(a + (b - c)) / 4;
}

}  // namespace tifa_libs::geo

#endif