#ifndef TIFA_LIBS_GEO3D_POINT3D
#define TIFA_LIBS_GEO3D_POINT3D

#include "../util/geo_util.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point3d {
  FP x, y, z;
  constexpr point3d(FP x = FP{}, FP y = FP{}, FP z = FP{}):
    x(x), y(y), z(z) {}

  friend std::istream &operator>>(std::istream &is, point3d &rhs) { return is >> rhs.x >> rhs.y >> rhs.z; }
  friend std::ostream &operator<<(std::ostream &os, point3d const &rhs) { return os << rhs.x << ' ' << rhs.y << ' ' << rhs.z; }

  // lhs * coord + rhs * (1 -coord)
  friend constexpr point3d lerp(point3d const &lhs, point3d const &rhs, FP coord) { return lhs * coord + rhs * (1 - coord); }

  friend constexpr point3d mid_point(point3d const &lhs, point3d const &rhs) { return lerp(lhs, rhs, 0.5); }

  constexpr point3d &operator+=(FP n) {
    this->x += n;
    this->y += n;
    this->z += n;
    return *this;
  }
  constexpr point3d operator+(FP n) const { return point3d(*this) += n; }
  constexpr point3d &operator-=(FP n) {
    this->x -= n;
    this->y -= n;
    this->z -= n;
    return *this;
  }
  constexpr point3d operator-(FP n) const { return point3d(*this) -= n; }
  constexpr point3d &operator*=(FP n) {
    this->x *= n;
    this->y *= n;
    this->z *= n;
    return *this;
  }
  constexpr point3d operator*(FP n) const { return point3d(*this) *= n; }
  constexpr point3d &operator/=(FP n) {
    this->x /= n;
    this->y /= n;
    this->z /= n;
    return *this;
  }
  constexpr point3d operator/(FP n) const { return point3d(*this) /= n; }

  constexpr point3d &operator+=(point3d const &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
  }
  constexpr point3d operator+(point3d const &rhs) const { return point3d(*this) += rhs; }
  constexpr point3d &operator-=(point3d const &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
  }
  constexpr point3d operator-(point3d const &rhs) const { return point3d(*this) -= rhs; }

  constexpr point3d operator-() const { return point3d{-x, -y, -z}; }
  constexpr bool operator<(point3d const &rhs) const {
    if (auto c = comp(x, rhs.x); c) return c >> 1;
    if (auto c = comp(y, rhs.y); c) return c >> 1;
    return comp(z, rhs.z) >> 1;
  }
  constexpr bool operator==(point3d const &rhs) const { return is_eq(x, rhs.x) && is_eq(y, rhs.y) && is_eq(z, rhs.z); }
  constexpr bool operator!=(point3d const &rhs) const { return !(*this == rhs); }

  constexpr FP operator*(point3d const &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
  constexpr point3d operator^(point3d const &rhs) const { return point3d{y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x}; }

  constexpr auto norm2() const { return x * x + y * y + z * z; }
  friend constexpr auto norm2(point3d const &lhs) { return lhs.norm2(); }

  constexpr auto norm() const { return std::hypot(x, y, z); }
  friend constexpr auto norm(point3d const &lhs) { return lhs.norm(); }
};

}  // namespace tifa_libs::geo

#endif