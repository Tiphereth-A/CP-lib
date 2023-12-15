#ifndef TIFALIBS_GEO2D_TRIANGLE
#define TIFALIBS_GEO2D_TRIANGLE

#include "ang_pp.hpp"
#include "cross.hpp"
#include "dist_pp.hpp"
#include "dot.hpp"

namespace tifa_libs::geo {

template <class FP>
struct triangle {
  point<FP> A, B, C;

  constexpr triangle() {}
  constexpr triangle(point<FP> const &a, point<FP> const &b, point<FP> const &c) : A(a), B(b), C(c) {}
  constexpr triangle(FP a_x, FP a_y, FP b_x, FP b_y, FP c_x, FP c_y) : A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}

  friend std::istream &operator>>(std::istream &is, triangle &t) { return is >> t.A >> t.B >> t.C; }
  friend std::ostream &operator<<(std::ostream &os, triangle const &t) { return os << t.A << ' ' << t.B << ' ' << t.C; }

  friend constexpr bool operator==(triangle const &l, triangle const &r) { return l.A == r.A && l.B == r.B && l.C == r.C; }

  // (a, b, c)
  constexpr pt3<FP> edges() const { return {dist_PP(B, C), dist_PP(C, A), dist_PP(A, B)}; }
  // (A, B, C)
  constexpr pt3<FP> angles() const { return {std::abs(ang_PP(C - A, B - A)), std::abs(ang_PP(A - B, C - B)), std::abs(ang_PP(A - C, B - C))}; }

  constexpr point<FP> trilinears(FP x, FP y, FP z) const {
    auto [a, b, c] = edges();
    x *= a, y *= b, z *= c;
    return (A * x + B * y + C * z) / (x + y + z);
  }
  constexpr point<FP> barycentrics(FP u, FP v, FP w) const { return (A * u + B * v + C * w) / (u + v + w); }
  constexpr FP area() const { return std::abs(cross(A, B, C)) / 2; }
  constexpr bool is_acute() const { return is_pos(dot(A, B, C)) && is_pos(dot(B, C, A)) && is_pos(dot(C, A, B)); }
  constexpr bool is_right() const { return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) || is_zero(dot(C, A, B)); }
  constexpr bool is_obtuse() const { return is_neg(dot(A, B, C)) || is_neg(dot(B, C, A)) || is_neg(dot(C, A, B)); }
};

}  // namespace tifa_libs::geo

#endif