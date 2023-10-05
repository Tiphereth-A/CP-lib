#ifndef TIFA_LIBS_GEO3D_POINT
#define TIFA_LIBS_GEO3D_POINT

#include "../util/geo_util.hpp"

namespace tifa_libs::geo2d {

template <class FP>
struct point {
  FP x, y, z;
  constexpr point(FP x = FP{}, FP y = FP{}, FP z = FP{}):
    x(x), y(y), z(z) {}

  friend std::istream &operator>>(std::istream &is, point &rhs) { return is >> rhs.x >> rhs.y >> rhs.z; }
  friend std::ostream &operator<<(std::ostream &os, point const &rhs) { return os << rhs.x << ' ' << rhs.y << ' ' << rhs.z; }

  // lhs * coord + rhs * (1 -coord)
  friend constexpr point lerp(point const &lhs, point const &rhs, FP coord) { return lhs * coord + rhs * (1 - coord); }

  friend constexpr point mid_point(point const &lhs, point const &rhs) { return lerp(lhs, rhs, 0.5); }

  constexpr point &operator+=(FP n) {
    this->x += n;
    this->y += n;
    this->z += n;
    return *this;
  }
  constexpr point operator+(FP n) const { return point(*this) += n; }
  constexpr point &operator-=(FP n) {
    this->x -= n;
    this->y -= n;
    this->z -= n;
    return *this;
  }
  constexpr point operator-(FP n) const { return point(*this) -= n; }
  constexpr point &operator*=(FP n) {
    this->x *= n;
    this->y *= n;
    this->z *= n;
    return *this;
  }
  constexpr point operator*(FP n) const { return point(*this) *= n; }
  constexpr point &operator/=(FP n) {
    this->x /= n;
    this->y /= n;
    this->z /= n;
    return *this;
  }
  constexpr point operator/(FP n) const { return point(*this) /= n; }

  constexpr point &operator+=(point const &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
  }
  constexpr point operator+(point const &rhs) const { return point(*this) += rhs; }
  constexpr point &operator-=(point const &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
  }
  constexpr point operator-(point const &rhs) const { return point(*this) -= rhs; }

  constexpr point operator-() const { return point{-x, -y, -z}; }
  constexpr bool operator<(point const &rhs) const {
    if (auto c = comp(x, rhs.x); c) return c >> 1;
    if (auto c = comp(y, rhs.y); c) return c >> 1;
    return comp(z, rhs.z) >> 1;
  }
  constexpr bool operator==(point const &rhs) const { return is_eq(x, rhs.x) && is_eq(y, rhs.y) && is_eq(z, rhs.z); }
  constexpr bool operator!=(point const &rhs) const { return !(*this == rhs); }

  constexpr FP operator*(point const &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
  constexpr point operator^(point const &rhs) const { return point{y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x}; }

  constexpr auto norm2() const { return x * x + y * y + z * z; }
  friend constexpr auto norm2(point const &lhs) { return lhs.norm2(); }

  constexpr auto norm() const { return std::hypot(x, y, z); }
  friend constexpr auto norm(point const &lhs) { return lhs.norm(); }
};

}  // namespace tifa_libs::geo2d

#endif