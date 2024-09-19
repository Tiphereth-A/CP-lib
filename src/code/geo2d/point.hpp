#ifndef TIFALIBS_GEO2D_POINT
#define TIFALIBS_GEO2D_POINT

#include "../util/fp_func.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point {
  using FP_t = FP;

  FP x, y;
  CEXPE point(FP x = FP{}, FP y = FP{}) : x(x), y(y) {}

  friend std::istream &operator>>(std::istream &is, point &p) { return is >> p.x >> p.y; }
  friend std::ostream &operator<<(std::ostream &os, point CR p) { return os << p.x << ' ' << p.y; }
  // s * r + t * (1 - r)
  template <std::floating_point T>
  friend CEXP point lerp(point CR s, point CR t, T r) { return s * r + t * (1 - r); }
  friend CEXP point mid_point(point CR s, point CR t) { return lerp(s, t, .5); }
  template <arithm_c T>
  CEXP point &operator+=(T n) { return this->x += n, this->y += n, *this; }
  template <arithm_c T>
  CEXP point &operator-=(T n) { return this->x -= n, this->y -= n, *this; }
  template <arithm_c T>
  CEXP point &operator*=(T n) { return this->x *= n, this->y *= n, *this; }
  template <arithm_c T>
  CEXP point &operator/=(T n) { return this->x /= n, this->y /= n, *this; }
  template <arithm_c T>
  friend CEXP point operator+(point x, T n) { return x += n; }
  template <arithm_c T>
  friend CEXP point operator+(T n, point x) { return x += n; }
  template <arithm_c T>
  friend CEXP point operator-(point x, T n) { return x -= n; }
  template <arithm_c T>
  friend CEXP point operator-(T n, point x) { return x -= n; }
  template <arithm_c T>
  friend CEXP point operator*(point x, T n) { return x *= n; }
  template <arithm_c T>
  friend CEXP point operator*(T n, point x) { return x *= n; }
  template <arithm_c T>
  friend CEXP point operator/(point x, T n) { return x /= n; }
  template <arithm_c T>
  friend CEXP point operator/(T n, point x) { return x /= n; }
  CEXP point &operator+=(point CR p) { return this->x += p.x, this->y += p.y, *this; }
  CEXP point &operator-=(point CR p) { return this->x -= p.x, this->y -= p.y, *this; }
  CEXP point operator+(point CR p) const { return point(*this) += p; }
  CEXP point operator-(point CR p) const { return point(*this) -= p; }
  CEXP point operator-() const { return point{-x, -y}; }
  CEXP auto operator<=>(point CR p) const {
    if (auto CR c = comp(x, p.x); c) return c;
    return comp(y, p.y);
  }
  CEXP bool operator==(point CR p) const { return is_eq(x, p.x) && is_eq(y, p.y); }
  CEXP FP operator*(point CR p) const { return x * p.x + y * p.y; }
  CEXP FP operator^(point CR p) const { return x * p.y - y * p.x; }
  CEXP FP arg() const {
    static_assert(std::is_floating_point_v<FP>);
    return std::atan2(y, x);
  }
  CEXP FP arg_2pi() const {
    FP res = arg();
    return is_neg(res) ? res + 2 * pi_v<FP> : res;
  }
  CEXP FP norm2() const { return x * x + y * y; }
  CEXP FP norm() const {
    static_assert(std::is_floating_point_v<FP>);
    return std::hypot(x, y);
  }
  CEXP point &do_unit() {
    static_assert(std::is_floating_point_v<FP>);
    return *this /= norm();
  }
  static CEXP u32 QUAD__[9] = {6, 7, 8, 5, 0, 1, 4, 3, 2};
  // 4 3 2
  // 5 0 1
  // 6 7 8
  CEXP u32 quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }
  CEXP int toleft(point CR p) const { return sgn(*this ^ p); }
  CEXP point &do_rot(FP theta) {
    const FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    return x = x0 * ct - y0 * st, y = x0 * st + y0 * ct, *this;
  }
  friend CEXP point rot(point p, FP theta) { return p.do_rot(theta); }
  CEXP point &do_rot90() {
    const FP _ = x;
    return x = -y, y = _, *this;
  }
  friend CEXP point rot90(point p) { return p.do_rot90(); }
  CEXP point &do_rot270() {
    const FP _ = y;
    return y = -x, x = _, *this;
  }
  friend CEXP point rot270(point p) { return p.do_rot270(); }
};

}  // namespace tifa_libs::geo

#endif