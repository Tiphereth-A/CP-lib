#ifndef TIFALIBS_GEO2D_CIRCLE
#define TIFALIBS_GEO2D_CIRCLE

#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
struct circle {
  point<FP> o;
  FP r;

  CEXP circle() = default;
  CEXP circle(point<FP> CR c, FP r) NE : o(c), r(r) {}
  CEXP circle(FP c_x, FP c_y, FP r_) NE : o(c_x, c_y), r(r_) {}

  friend auto& operator>>(istream_c auto& is, circle& c) NE { return is >> c.o >> c.r; }
  friend auto& operator<<(ostream_c auto& os, circle CR c) NE { return os << c.o << ' ' << c.r; }
  friend CEXP bool operator==(circle CR l, circle CR r) NE { return l.o == r.o && l.r == r.r; }
  friend CEXP auto operator<=>(circle CR l, circle CR r) NE {
    if (auto c = l.o <=> r.o; c) return c;
    return comp(l.r, r.r);
  }

  CEXP FP area(FP angle = pi_v<FP> * 2) CNE { return angle * r * r / 2; }
  CEXP FP crown_area(FP angle = pi_v<FP> * 2) CNE { return (angle - std::sin(angle)) * r * r / 2; }
  CEXP FP arc(FP angle = pi_v<FP> * 2) CNE { return angle * r; }
};

}  // namespace tifa_libs::geo

#endif