#ifndef TIFA_LIBS_GEO2D_POINT_CLASS
#define TIFA_LIBS_GEO2D_POINT_CLASS

#include "util.hpp"

namespace tifa_libs::geo2d {

template <class FP>
struct point {
  FP x, y;
  constexpr point(FP x = FP{}, FP y = FP{}):
    x(x), y(y) {}

  friend std::istream &operator>>(std::istream &is, point &rhs) { return is >> rhs.x >> rhs.y; }
  friend std::ostream &operator<<(std::ostream &os, point const &rhs) { return os << rhs.x << ' ' << rhs.y; }

  // lhs * coord + rhs * (1 -coord)
  friend constexpr point lerp(point const &lhs, point const &rhs, FP coord) { return lhs * coord + rhs * (1 - coord); }

  friend constexpr point mid_point(point const &lhs, point const &rhs) { return lerp(lhs, rhs, 0.5); }

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

  constexpr point &operator+=(point const &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }
  constexpr point operator+(point const &rhs) const { return point(*this) += rhs; }
  constexpr point &operator-=(point const &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }
  constexpr point operator-(point const &rhs) const { return point(*this) -= rhs; }

  constexpr point operator-() const { return point{-x, -y}; }
  constexpr bool operator<(point const &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  constexpr bool operator==(point const &rhs) const { return is_eq(x, rhs.x) && is_eq(y, rhs.y); }
  constexpr bool operator!=(point const &rhs) const { return !(*this == rhs); }

  constexpr FP operator*(point const &rhs) const { return x * rhs.x + y * rhs.y; }
  constexpr FP operator^(point const &rhs) const { return x * rhs.y - y * rhs.x; }

  constexpr auto arg() const { return std::atan2(y, x); }
  friend constexpr auto arg(point const &lhs) { return lhs.arg(); }

  // result in [0, 2pi)
  constexpr auto arg2pi() const {
    FP tmp_ = arg();
    return is_neg(tmp_) ? tmp_ + 2 * PI : tmp_;
  }
  // result in [0, 2pi)
  friend constexpr auto arg2pi(point const &lhs) { return lhs.arg2pi(); }

  constexpr auto norm2() const { return x * x + y * y; }
  friend constexpr auto norm2(point const &lhs) { return lhs.norm2(); }

  constexpr auto norm() const { return sqrt(norm2()); }
  friend constexpr auto norm(point const &lhs) { return lhs.norm(); }

  constexpr static int QUAD__[9] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
  constexpr auto quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }
  friend constexpr auto quad(point const &lhs) { return lhs.quad(); }

  constexpr point &do_rot90() {
    FP tmp = x;
    x = -y;
    y = tmp;
    return *this;
  }
  friend constexpr point rot90(point lhs) { return lhs.do_rot90(); }

  constexpr point &do_rot270() {
    FP tmp = y;
    y = -x;
    x = tmp;
    return *this;
  }
  friend constexpr point rot270(point lhs) { return lhs.do_rot270(); }

  constexpr point &do_unit() { return *this /= norm(); }
  friend constexpr point unit(point lhs) { return lhs.do_unit(); }

  constexpr point &do_rot(FP theta) {
    FP _x = x, _y = y;
    x = _x * std::cos(theta) - _y * std::sin(theta);
    y = _x * std::sin(theta) + _y * std::cos(theta);
    return *this;
  }
  friend constexpr point rot(point lhs, FP theta) { return lhs.do_rot(theta); }
};

}  // namespace tifa_libs::geo2d

#endif