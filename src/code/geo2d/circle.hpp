#ifndef TIFA_LIBS_GEO2D_CIRCLE
#define TIFA_LIBS_GEO2D_CIRCLE

#include "../util/geo_util.hpp"
#include "point.hpp"

namespace tifa_libs::geo {

template <class FP>
struct circle {
  point<FP> o;
  FP r;
  circle() {}
  constexpr circle(point<FP> const &c, FP r) : o(c), r(r) {}
  constexpr circle(FP c_x, FP c_y, FP r_) : o(c_x, c_y), r(r_) {}
  friend std::istream &operator>>(std::istream &is, circle &c) { return is >> c.o >> c.r; }
  friend std::ostream &operator<<(std::ostream &os, circle const &c) { return os << c.o << ' ' << c.r; }
  friend bool operator==(circle const &l, circle const &r) { return l.o == r.o && l.r == r.r; }

  constexpr FP area(FP angle = PI<FP> * 2) const { return angle * r * r / 2; }
  constexpr FP crown_area(FP angle = PI<FP> * 2) const { return (angle - std::sin(angle)) * r * r / 2; }
  constexpr FP arc(FP angle = PI<FP> * 2) const { return angle * r; }
};

}  // namespace tifa_libs::geo

#endif