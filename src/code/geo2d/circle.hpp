#ifndef TIFALIBS_GEO2D_CIRCLE
#define TIFALIBS_GEO2D_CIRCLE

#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
struct circle {
  point<FP> o;
  FP r;
  CEXP circle() {}

  CEXP circle(point<FP> CR c, FP r) : o(c), r(r) {}
  CEXP circle(FP c_x, FP c_y, FP r_) : o(c_x, c_y), r(r_) {}

  friend std::istream &operator>>(std::istream &is, circle &c) { return is >> c.o >> c.r; }
  friend std::ostream &operator<<(std::ostream &os, circle CR c) { return os << c.o << ' ' << c.r; }
  friend CEXP bool operator==(circle CR l, circle CR r) { return l.o == r.o && l.r == r.r; }

  CEXP FP area(FP angle = pi_v<FP> * 2) const { return angle * r * r / 2; }
  CEXP FP crown_area(FP angle = pi_v<FP> * 2) const { return (angle - std::sin(angle)) * r * r / 2; }
  CEXP FP arc(FP angle = pi_v<FP> * 2) const { return angle * r; }
};

}  // namespace tifa_libs::geo

#endif