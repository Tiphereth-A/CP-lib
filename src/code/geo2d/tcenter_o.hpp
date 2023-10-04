#ifndef TIFA_LIBS_GEO2D_TCENTER_O
#define TIFA_LIBS_GEO2D_TCENTER_O

#include "ins_ll.hpp"
#include "triangle.hpp"

namespace tifa_libs::geo2d {

// radius of circumscribed circle
template <class FP>
constexpr FP radius_O(triangle<FP> const &t) {
  FP ab = dist_PP(t.A, t.B), bc = dist_PP(t.B, t.C), ca = dist_PP(t.C, t.A);
  return ab * bc * ca / (4 * t.area());
}

// circumcenter (X3)
template <class FP>
constexpr point<FP> center_O(triangle<FP> const &t) {
  point<FP> p1 = mid_point(t.B, t.C), p2 = mid_point(t.C, t.A);
  return ins_LL({p1, p1 + (t.B - t.C).do_rot90()}, {p2, p2 + (t.C - t.A).do_rot90()});
}

}  // namespace tifa_libs::geo2d

#endif
