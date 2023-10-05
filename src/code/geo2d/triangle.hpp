#ifndef TIFA_LIBS_GEO2D
#define TIFA_LIBS_GEO2D

#include "cross.hpp"
#include "dot.hpp"

namespace tifa_libs::geo {

template <class FP>
struct triangle {
  point<FP> A, B, C;
  triangle() {}
  constexpr triangle(point<FP> const &a, point<FP> const &b, point<FP> const &c):
    A(a), B(b), C(c) {}
  constexpr triangle(FP a_x, FP a_y, FP b_x, FP b_y, FP c_x, FP c_y):
    A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}

  friend std::istream &operator>>(std::istream &is, triangle &t) { return is >> t.A >> t.B >> t.C; }
  friend std::ostream &operator<<(std::ostream &os, triangle const &t) { return os << t.A << ' ' << t.B << ' ' << t.C; }

  friend bool operator==(triangle const &l, triangle const &r) { return l.A == r.A && l.B == r.B && l.C == r.C; }

  constexpr FP area() const { return std::abs(cross(A, B, C)) / 2; }

  constexpr point<FP> average_w(FP wA, FP wB, FP wC) const { return (A * wA + B * wB + C * wC) / (wA + wB + wC); }

  constexpr bool is_acute() const { return is_pos(dot(A, B, C)) && is_pos(dot(B, C, A)) && is_pos(dot(C, A, B)); }
  constexpr bool is_right() const { return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) || is_zero(dot(C, A, B)); }
  constexpr bool is_obtuse() const { return is_neg(dot(A, B, C)) || is_neg(dot(B, C, A)) || is_neg(dot(C, A, B)); }
};

}  // namespace tifa_libs::geo

#endif