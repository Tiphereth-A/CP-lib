#ifndef TIFALIBS_GEO2D_AREA_TRIAEDGES
#define TIFALIBS_GEO2D_AREA_TRIAEDGES

#include "../util/util.hpp"

namespace tifa_libs::geo {

// calculate area of triangle by the length of 3 edges
// numerical stability improved
template <class FP>
constexpr FP area_T_abc(FP a, FP b, FP c) {
  if (a < b) std::swap(a, b);
  if (a < c) std::swap(a, c);
  if (b < c) std::swap(b, c);
  return std::sqrt(a + (b + c)) * std::sqrt(c - (a - b)) * std::sqrt(c + (a - b)) * std::sqrt(a + (b - c)) / 4;
}

}  // namespace tifa_libs::geo

#endif