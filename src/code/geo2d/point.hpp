#ifndef TIFALIBS_GEO2D_POINT
#define TIFALIBS_GEO2D_POINT

#include "../util/fp_comp.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point {
  FP x, y;
  explicit constexpr point(FP x = FP{}, FP y = FP{}) : x(x), y(y) {}

  friend std::istream &operator>>(std::istream &is, point &p) { return is >> p.x >> p.y; }
  friend std::ostream &operator<<(std::ostream &os, point const &p) { return os << p.x << ' ' << p.y; }

  // s * r + t * (1 - r)
  friend constexpr point lerp(point const &s, point const &t, FP r) { return s * r + t * (1 - r); }
  friend constexpr point mid_point(point const &s, point const &t) { return lerp(s, t, .5); }

  constexpr point &operator+=(FP n) {
    this->x += n;
    this->y += n;
    return *this;
  }
  constexpr point &operator-=(FP n) {
    this->x -= n;
    this->y -= n;
    return *this;
  }
  constexpr point &operator*=(FP n) {
    this->x *= n;
    this->y *= n;
    return *this;
  }
  constexpr point &operator/=(FP n) {
    this->x /= n;
    this->y /= n;
    return *this;
  }
  friend constexpr point operator+(point x, FP n) { return x += n; }
  friend constexpr point operator+(FP n, point x) { return x += n; }
  friend constexpr point operator-(point x, FP n) { return x -= n; }
  friend constexpr point operator-(FP n, point x) { return x -= n; }
  friend constexpr point operator*(point x, FP n) { return x *= n; }
  friend constexpr point operator*(FP n, point x) { return x *= n; }
  friend constexpr point operator/(point x, FP n) { return x /= n; }
  friend constexpr point operator/(FP n, point x) { return x /= n; }

  constexpr point &operator+=(point const &p) {
    this->x += p.x;
    this->y += p.y;
    return *this;
  }
  constexpr point &operator-=(point const &p) {
    this->x -= p.x;
    this->y -= p.y;
    return *this;
  }
  constexpr point operator+(point const &p) const { return point(*this) += p; }
  constexpr point operator-(point const &p) const { return point(*this) -= p; }

  constexpr point operator-() const { return point{-x, -y}; }
  constexpr auto operator<=>(point const &p) const {
    if (auto c = comp(x, p.x); c) return c;
    return comp(y, p.y);
  }
  constexpr bool operator==(point const &p) const { return is_eq(x, p.x) && is_eq(y, p.y); }

  constexpr FP operator*(point const &p) const { return x * p.x + y * p.y; }
  constexpr FP operator^(point const &p) const { return x * p.y - y * p.x; }

  constexpr auto arg() const { return std::atan2(y, x); }
  constexpr FP norm2() const { return x * x + y * y; }
  constexpr FP norm() const { return std::hypot(x, y); }
  constexpr point &do_unit() { return *this /= norm(); }

  static constexpr u32 QUAD__[9] = {6, 7, 8, 5, 0, 1, 4, 3, 2};
  // 4 3 2
  // 5 0 1
  // 6 7 8
  constexpr u32 quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }

  constexpr point &do_rot(FP theta) {
    FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    x = x0 * ct - y0 * st;
    y = x0 * st + y0 * ct;
    return *this;
  }
  constexpr point &do_rot90() {
    FP tmp = x;
    x = -y;
    y = tmp;
    return *this;
  }
  friend constexpr point rot90(point p) { return p.do_rot90(); }
  constexpr point &do_rot270() {
    FP tmp = y;
    y = -x;
    x = tmp;
    return *this;
  }
  friend constexpr point rot270(point p) { return p.do_rot270(); }
};

}  // namespace tifa_libs::geo

#endif