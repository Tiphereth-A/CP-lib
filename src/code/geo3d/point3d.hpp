#ifndef TIFA_LIBS_GEO3D_POINT3D
#define TIFA_LIBS_GEO3D_POINT3D

#include "../util/geo_util.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point3d {
  FP x, y, z;
  explicit constexpr point3d(FP x = FP{}, FP y = FP{}, FP z = FP{}) : x(x), y(y), z(z) {}

  friend std::istream &operator>>(std::istream &is, point3d &p) { return is >> p.x >> p.y >> p.z; }
  friend std::ostream &operator<<(std::ostream &os, point3d const &p) { return os << p.x << ' ' << p.y << ' ' << p.z; }

  // s * r + t * (1 - r)
  friend constexpr point3d lerp(point3d const &s, point3d const &t, FP r) { return s * r + t * (1 - r); }

  friend constexpr point3d mid_point(point3d const &s, point3d const &t) { return lerp(s, t, .5); }

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

  constexpr point3d &operator+=(point3d const &p) {
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;
    return *this;
  }
  constexpr point3d operator+(point3d const &p) const { return point3d(*this) += p; }
  constexpr point3d &operator-=(point3d const &p) {
    this->x -= p.x;
    this->y -= p.y;
    this->z -= p.z;
    return *this;
  }
  constexpr point3d operator-(point3d const &p) const { return point3d(*this) -= p; }

  constexpr point3d operator-() const { return point3d{-x, -y, -z}; }
  constexpr bool operator<(point3d const &p) const {
    if (auto c = comp(x, p.x); c) return c >> 1;
    if (auto c = comp(y, p.y); c) return c >> 1;
    return comp(z, p.z) >> 1;
  }
  constexpr bool operator==(point3d const &p) const { return is_eq(x, p.x) && is_eq(y, p.y) && is_eq(z, p.z); }
  constexpr bool operator!=(point3d const &p) const { return !(*this == p); }

  constexpr FP operator*(point3d const &p) const { return x * p.x + y * p.y + z * p.z; }
  constexpr point3d operator^(point3d const &p) const { return point3d{y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x}; }

  constexpr auto norm2() const { return x * x + y * y + z * z; }
  friend constexpr auto norm2(point3d const &p) { return p.norm2(); }

  constexpr auto norm() const { return std::hypot(x, y, z); }
  friend constexpr auto norm(point3d const &p) { return p.norm(); }
};

}  // namespace tifa_libs::geo

#endif