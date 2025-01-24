#ifndef TIFALIBS_GEO2D_DIST_PP
#define TIFALIBS_GEO2D_DIST_PP

#include "point.hpp"

namespace tifa_libs::geo {

// distance of two points
// @return $(|x_1-x_2|^p + |y_1-y_2|^p)^{1/p}$, p = 0 means $\infty$
template <class FP, u32 p = 2>
CEXP FP dist_PP(point<FP> CR p1, point<FP> CR p2) NE {
  static_assert(p < 2 || std::floating_point<FP>);
  if CEXP (p == 0) return max(abs(p1.x - p2.x), abs(p1.y - p2.y));   // Chebyshev
  else if CEXP (p == 1) return abs(p1.x - p2.x) + abs(p1.y - p2.y);  // Manhattan
  else if CEXP (p == 2) return (p1 - p2).norm();                     // Euclidian
  else return std::pow(std::pow(abs(p1.x - p2.x), p) + std::pow(abs(p1.y - p2.y), p), FP{1} / p);
}

}  // namespace tifa_libs::geo

#endif