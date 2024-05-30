#ifndef TIFALIBS_GEO2D_TCENTER_O
#define TIFALIBS_GEO2D_TCENTER_O

#include "ins_ll.hpp"
#include "triangle.hpp"

namespace tifa_libs::geo {

// radius of circumscribed circle
template <class FP>
CEXP FP radius_O(triangle<FP> CR t) { return dist_PP(t.B, t.C) / std::sin(abs(ang_PP(t.B - t.A, t.C - t.A))) / 2; }

// circumcenter (X3)
template <class FP>
CEXP point<FP> center_O(triangle<FP> CR t) {
  // auto [A, B, C] = t.angles();
  // return t.trilinears(std::cos(A), std::cos(B), std::cos(C));
  const point<FP> p1 = mid_point(t.B, t.C), p2 = mid_point(t.C, t.A);
  return ins_LL<FP>({p1, p1 + (t.B - t.C).do_rot90()}, {p2, p2 + (t.C - t.A).do_rot90()});
}

}  // namespace tifa_libs::geo

#endif