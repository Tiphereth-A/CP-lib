#ifndef TIFA_LIBS_GEO2D_POINT
#define TIFA_LIBS_GEO2D_POINT

#include "../util/geo_util.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point {
  FP x, y;
  explicit constexpr point(FP x = FP{}, FP y = FP{}) : x(x), y(y) {}

  friend std::istream &operator>>(std::istream &is, point &p) { return is >> p.x >> p.y; }
  friend std::ostream &operator<<(std::ostream &os, point const &p) { return os << p.x << ' ' << p.y; }

  // s * r + t * (1 - r)
  friend constexpr point lerp(point const &s, point const &t, FP r) { return s * r + t * (1 - r); }

  friend constexpr point mid_point(point const &s, point const &t) { return lerp(s, t, 0.5); }

  constexpr point &operator+=(FP n) {
    this->x += n;
    this->y += n;
    return *this;
  }
  constexpr point operator+(FP n) const { return point(*this) += n; }
  constexpr point &operator-=(FP n) {
    this->x -= n;
    this->y -= n;
    return *this;
  }
  constexpr point operator-(FP n) const { return point(*this) -= n; }
  constexpr point &operator*=(FP n) {
    this->x *= n;
    this->y *= n;
    return *this;
  }
  constexpr point operator*(FP n) const { return point(*this) *= n; }
  constexpr point &operator/=(FP n) {
    this->x /= n;
    this->y /= n;
    return *this;
  }
  constexpr point operator/(FP n) const { return point(*this) /= n; }

  constexpr point &operator+=(point const &p) {
    this->x += p.x;
    this->y += p.y;
    return *this;
  }
  constexpr point operator+(point const &p) const { return point(*this) += p; }
  constexpr point &operator-=(point const &p) {
    this->x -= p.x;
    this->y -= p.y;
    return *this;
  }
  constexpr point operator-(point const &p) const { return point(*this) -= p; }

  constexpr point operator-() const { return point{-x, -y}; }
  constexpr bool operator<(point const &p) const {
    if (auto c = comp(x, p.x); c) return c >> 1;
    return comp(y, p.y) >> 1;
  }
  constexpr bool operator==(point const &p) const { return is_eq(x, p.x) && is_eq(y, p.y); }
  constexpr bool operator!=(point const &p) const { return !(*this == p); }

  constexpr FP operator*(point const &p) const { return x * p.x + y * p.y; }
  constexpr FP operator^(point const &p) const { return x * p.y - y * p.x; }

  constexpr auto arg() const { return std::atan2(y, x); }
  friend constexpr auto arg(point const &p) { return p.arg(); }

  // result in [0, 2pi)
  constexpr auto arg2pi() const {
    FP _ = arg();
    return is_neg(_) ? _ + 2 * PI : _;
  }
  // result in [0, 2pi)
  friend constexpr auto arg2pi(point const &p) { return p.arg2pi(); }

  constexpr auto norm2() const { return x * x + y * y; }
  friend constexpr auto norm2(point const &p) { return p.norm2(); }

  constexpr auto norm() const { return std::hypot(x, y); }
  friend constexpr auto norm(point const &p) { return p.norm(); }

  constexpr static int QUAD__[9] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
  constexpr auto quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }
  friend constexpr auto quad(point const &p) { return p.quad(); }

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

  constexpr point &do_unit() { return *this /= norm(); }
  friend constexpr point unit(point p) { return p.do_unit(); }

  constexpr point &do_rot(FP theta) {
    FP _x = x, _y = y;
    x = _x * std::cos(theta) - _y * std::sin(theta);
    y = _x * std::sin(theta) + _y * std::cos(theta);
    return *this;
  }
  friend constexpr point rot(point p, FP theta) { return p.do_rot(theta); }
};

}  // namespace tifa_libs::geo

#endif