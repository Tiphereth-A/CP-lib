#ifndef TIFALIBS_GEO2D_POINT
#define TIFALIBS_GEO2D_POINT

#include "../util/fp_comp.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point {
  FP x, y;
  explicit CEXP point(FP x = FP{}, FP y = FP{}) : x(x), y(y) {}

  friend std::istream &operator>>(std::istream &is, point &p) { return is >> p.x >> p.y; }
  friend std::ostream &operator<<(std::ostream &os, point CR p) { return os << p.x << ' ' << p.y; }

  // s * r + t * (1 - r)
  friend CEXP point lerp(point CR s, point CR t, FP r) { return s * r + t * (1 - r); }
  friend CEXP point mid_point(point CR s, point CR t) { return lerp(s, t, .5); }

  CEXP point &operator+=(FP n) {
    this->x += n;
    this->y += n;
    return *this;
  }
  CEXP point &operator-=(FP n) {
    this->x -= n;
    this->y -= n;
    return *this;
  }
  CEXP point &operator*=(FP n) {
    this->x *= n;
    this->y *= n;
    return *this;
  }
  CEXP point &operator/=(FP n) {
    this->x /= n;
    this->y /= n;
    return *this;
  }
  friend CEXP point operator+(point x, FP n) { return x += n; }
  friend CEXP point operator+(FP n, point x) { return x += n; }
  friend CEXP point operator-(point x, FP n) { return x -= n; }
  friend CEXP point operator-(FP n, point x) { return x -= n; }
  friend CEXP point operator*(point x, FP n) { return x *= n; }
  friend CEXP point operator*(FP n, point x) { return x *= n; }
  friend CEXP point operator/(point x, FP n) { return x /= n; }
  friend CEXP point operator/(FP n, point x) { return x /= n; }

  CEXP point &operator+=(point CR p) {
    this->x += p.x;
    this->y += p.y;
    return *this;
  }
  CEXP point &operator-=(point CR p) {
    this->x -= p.x;
    this->y -= p.y;
    return *this;
  }
  CEXP point operator+(point CR p) const { return point(*this) += p; }
  CEXP point operator-(point CR p) const { return point(*this) -= p; }

  CEXP point operator-() const { return point{-x, -y}; }
  CEXP auto operator<=>(point CR p) const {
    if (auto c = comp(x, p.x); c) return c;
    return comp(y, p.y);
  }
  CEXP bool operator==(point CR p) const { return is_eq(x, p.x) && is_eq(y, p.y); }

  CEXP FP operator*(point CR p) const { return x * p.x + y * p.y; }
  CEXP FP operator^(point CR p) const { return x * p.y - y * p.x; }

  CEXP auto arg() const { return std::atan2(y, x); }
  CEXP FP norm2() const { return x * x + y * y; }
  CEXP FP norm() const { return std::hypot(x, y); }
  CEXP point &do_unit() { return *this /= norm(); }

  static CEXP u32 QUAD__[9] = {6, 7, 8, 5, 0, 1, 4, 3, 2};
  // 4 3 2
  // 5 0 1
  // 6 7 8
  CEXP u32 quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }

  CEXP point &do_rot(FP theta) {
    FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    x = x0 * ct - y0 * st;
    y = x0 * st + y0 * ct;
    return *this;
  }
  CEXP point &do_rot90() {
    FP tmp = x;
    x = -y;
    y = tmp;
    return *this;
  }
  friend CEXP point rot90(point p) { return p.do_rot90(); }
  CEXP point &do_rot270() {
    FP tmp = y;
    y = -x;
    x = tmp;
    return *this;
  }
  friend CEXP point rot270(point p) { return p.do_rot270(); }
};

}  // namespace tifa_libs::geo

#endif