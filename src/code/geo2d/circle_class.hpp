#ifndef TIFA_LIBS_GEO2D_CIRCLE_CLASS
#define TIFA_LIBS_GEO2D_CIRCLE_CLASS

#include "point_class.hpp"
#include "util.hpp"

namespace tifa_libs::geo2d {

template <class FP>
struct circle {
  point<FP> o;
  FP r;
  circle() {}
  constexpr circle(point<FP> const &c, FP r):
    o(c), r(r) {}
  constexpr circle(const FP &c_x, const FP &c_y, FP r_):
    o(c_x, c_y), r(r_) {}
  friend std::istream &operator>>(std::istream &is, circle &rhs) { return is >> rhs.o >> rhs.r; }
  friend std::ostream &operator<<(std::ostream &os, circle const &rhs) { return os << rhs.o << ' ' << rhs.r; }
  friend bool operator==(circle const &lhs, circle const &rhs) { return lhs.o == rhs.o && lhs.r == rhs.r; }

  constexpr FP area(FP angle = PI * 2) const { return angle * r * r / 2; }
  constexpr FP crown_area(FP angle = PI * 2) const { return (angle - std::sin(angle)) * r * r / 2; }
  constexpr FP arc(FP angle = PI * 2) const { return angle * r; }
};

}  // namespace tifa_libs::geo2d

#endif