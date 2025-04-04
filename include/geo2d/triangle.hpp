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

  CEXP triangle() = default;
  CEXP triangle(point<FP> CR a, point<FP> CR b, point<FP> CR c) NE : A(a), B(b), C(c) {}
  CEXP triangle(FP a_x, FP a_y, FP b_x, FP b_y, FP c_x, FP c_y) NE : A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}

  friend auto &operator>>(istream_c auto &is, triangle &t) NE { return is >> t.A >> t.B >> t.C; }
  friend auto &operator<<(ostream_c auto &os, triangle CR t) NE { return os << t.A << ' ' << t.B << ' ' << t.C; }
  friend CEXP bool operator==(triangle CR l, triangle CR r) NE { return l.A == r.A && l.B == r.B && l.C == r.C; }
  // (a, b, c)
  CEXP pt3<FP> edges() CNE { return {dist_PP(B, C), dist_PP(C, A), dist_PP(A, B)}; }
  // (A, B, C)
  CEXP pt3<FP> angles() CNE { return {abs(ang_PP(C - A, B - A)), abs(ang_PP(A - B, C - B)), abs(ang_PP(A - C, B - C))}; }
  CEXP point<FP> trilinears(FP x, FP y, FP z) CNE {
    auto [a, b, c] = edges();
    x *= a, y *= b, z *= c;
    return (A * x + B * y + C * z) / (x + y + z);
  }
  CEXP point<FP> barycentrics(FP u, FP v, FP w) CNE { return (A * u + B * v + C * w) / (u + v + w); }
  CEXP FP area() CNE { return abs(cross(A, B, C)) / 2; }
  CEXP bool is_acute() CNE { return is_pos(dot(A, B, C)) && is_pos(dot(B, C, A)) && is_pos(dot(C, A, B)); }
  CEXP bool is_right() CNE { return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) || is_zero(dot(C, A, B)); }
  CEXP bool is_obtuse() CNE { return is_neg(dot(A, B, C)) || is_neg(dot(B, C, A)) || is_neg(dot(C, A, B)); }
};

}  // namespace tifa_libs::geo

#endif