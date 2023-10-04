#ifndef TIFA_LIBS_GEO2D_TRIANGLE_CLASS
#define TIFA_LIBS_GEO2D_TRIANGLE_CLASS

#include "util.hpp"

#include "line.hpp"
#include "point.hpp"

namespace tifa_libs::geo2d {

template <class FP>
struct triangle {
  point<FP> A, B, C;
  triangle() {}
  constexpr triangle(point<FP> const &a, point<FP> const &b, point<FP> const &c):
    A(a), B(b), C(c) {}
  constexpr triangle(const FP &a_x, const FP &a_y, const FP &b_x, const FP &b_y, const FP &c_x, const FP &c_y):
    A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}

  friend std::istream &operator>>(std::istream &is, triangle &rhs) { return is >> rhs.A >> rhs.B >> rhs.C; }
  friend std::ostream &operator<<(std::ostream &os, triangle const &rhs) { return os << rhs.A << ' ' << rhs.B << ' ' << rhs.C; }

  friend bool operator==(triangle const &lhs, triangle const &rhs) { return lhs.A == rhs.A && lhs.B == rhs.B && lhs.C == rhs.C; }

  constexpr FP area() const { return std::abs(cross(A, B, C)) / 2; }

  constexpr point<FP> average_w(FP wA, FP wB, FP wC) const { return (A * wA + B * wB + C * wC) / (wA + wB + wC); }

  constexpr bool is_acute() const { return is_pos(dot(A, B, C)) && is_pos(dot(B, C, A)) && is_pos(dot(C, A, B)); }
  constexpr bool is_right() const { return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) || is_zero(dot(C, A, B)); }
  constexpr bool is_obtuse() const { return is_neg(dot(A, B, C)) || is_neg(dot(B, C, A)) || is_neg(dot(C, A, B)); }

  // radius of inscribed circle
  constexpr FP radius_I() const {
    FP ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return 2 * area() / (ab + bc + ca);
  }
  // radius of circumscribed circle
  constexpr FP radius_O() const {
    FP ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return ab * bc * ca / (4 * area());
  }

  // incenter (X1)
  constexpr point<FP> center_I() const { return average_w((B - C).abs(), (C - A).abs(), (A - B).abs()); }
  //! excenter of A
  constexpr point<FP> center_E() const { return average_w(-((B - C).abs()), (C - A).abs(), (A - B).abs()); }
  // centroid (X2)
  constexpr point<FP> center_G() const { return average_w(1, 1, 1); }
  // circumcenter (X3)
  constexpr point<FP> center_O() const {
    point p1 = mid_point(B, C), p2 = mid_point(C, A);
    return ins_LL({p1, p1 + (B - C).do_rot90()}, {p2, p2 + (C - A).do_rot90()});
  }
  // orthocenter (X4)
  constexpr point<FP> center_H() const { return ins_LL({A, A + (B - C).do_rot90()}, {B, B + (C - A).do_rot90()}); }
  // 9-point center (X5)
  constexpr point<FP> center_N() const { return mid_point(center_O(), center_H()); }
  // fermat center (X13)
  point<FP> center_X() const {
    FP s3 = sqrt(FP{3}), r = radius_I(), R = radius_O(), s = ((A - B).abs() + (B - C).abs() + (C - A).abs()) / 2;
    return center_I() * (s3 * (r * r + 2 * r * R + s * s)) + center_O() * (-6 * r * (s3 * R - 2 * s)) + center_G() * (-2 * r * (s3 * r + 3 * s));
  }
};

}  // namespace tifa_libs::geo2d

#endif