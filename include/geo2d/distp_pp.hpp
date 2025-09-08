#ifndef TIFALIBS_GEO2D_DISTP_PP
#define TIFALIBS_GEO2D_DISTP_PP

#include "../math/qpow.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// distance of two points
// @return Chebyshev dis if p = 0, otherwise $(|x_1-x_2|^p + |y_1-y_2|^p)$
template <class FP, u32 p = 2>
CEXP FP distp_PP(point<FP> CR p1, point<FP> CR p2) NE {
  if CEXP (p == 0) return max(abs(p1.x - p2.x), abs(p1.y - p2.y));   // Chebyshev
  else if CEXP (p == 1) return abs(p1.x - p2.x) + abs(p1.y - p2.y);  // Manhattan
  else if CEXP (p == 2) return (p1 - p2).norm2();                    // Euclidian
  else return math::qpow(abs(p1.x - p2.x), p) + math::qpow(abs(p1.y - p2.y), p);
}

template <class FP, u32 p = 2>
CEXP auto comp_distp(point<FP> CR p1, point<FP> CR p2, FP r) NE {
  if CEXP (std::floating_point<FP>) return comp(dist_PP<FP, p>(p1, p2), r);
  else return comp(distp_PP<FP, p>(p1, p2), qpow(r, p ? p : 1));
}
template <class FP, u32 p = 2>
CEXP auto comp_distp(point<FP> CR p1, point<FP> CR p2, point<FP> CR q1, point<FP> CR q2) NE {
  if CEXP (std::floating_point<FP>) return comp(dist_PP<FP, p>(p1, p2), dist_PP<FP, p>(q1, q2));
  else return comp(distp_PP<FP, p>(p1, p2), distp_PP<FP, p>(q1, q2));
}

}  // namespace tifa_libs::geo

#endif