#ifndef TIFALIBS_GEO3D_POINT3D
#define TIFALIBS_GEO3D_POINT3D

#include "../util/util.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point3d {
  using FP_t = FP;
  FP x, y, z;
  explicit CEXP point3d(FP x = FP{}, FP y = FP{}, FP z = FP{}) : x(x), y(y), z(z) {}

  friend std::istream &operator>>(std::istream &is, point3d &p) { return is >> p.x >> p.y >> p.z; }
  friend std::ostream &operator<<(std::ostream &os, point3d CR p) { return os << p.x << ' ' << p.y << ' ' << p.z; }
  // s * r + t * (1 - r)
  friend CEXP point3d lerp(point3d CR s, point3d CR t, FP r) {
    static_assert(std::floating_point<FP>);
    return s * r + t * (1 - r);
  }
  friend CEXP point3d mid_point(point3d CR s, point3d CR t) { return lerp(s, t, .5); }
  CEXP point3d &operator+=(FP n) { return this->x += n, this->y += n, this->z += n, *this; }
  CEXP point3d operator+(FP n) const { return point3d(*this) += n; }
  CEXP point3d &operator-=(FP n) { return this->x -= n, this->y -= n, this->z -= n, *this; }
  CEXP point3d operator-(FP n) const { return point3d(*this) -= n; }
  CEXP point3d &operator*=(FP n) { return this->x *= n, this->y *= n, this->z *= n, *this; }
  CEXP point3d operator*(FP n) const { return point3d(*this) *= n; }
  CEXP point3d &operator/=(FP n) { return this->x /= n, this->y /= n, this->z /= n, *this; }
  CEXP point3d operator/(FP n) const { return point3d(*this) /= n; }
  CEXP point3d &operator+=(point3d CR p) { return this->x += p.x, this->y += p.y, this->z += p.z, *this; }
  CEXP point3d operator+(point3d CR p) const { return point3d(*this) += p; }
  CEXP point3d &operator-=(point3d CR p) { return this->x -= p.x, this->y -= p.y, this->z -= p.z, *this; }
  CEXP point3d operator-(point3d CR p) const { return point3d(*this) -= p; }
  CEXP point3d operator-() const { return point3d{-x, -y, -z}; }
  CEXP auto operator<=>(point3d CR p) const {
    if (auto c = comp(x, p.x); c) return c;
    if (auto c = comp(y, p.y); c) return c;
    return comp(z, p.z);
  }
  CEXP bool operator==(point3d CR p) const { return is_eq(x, p.x) && is_eq(y, p.y) && is_eq(z, p.z); }
  CEXP FP operator*(point3d CR p) const { return x * p.x + y * p.y + z * p.z; }
  CEXP point3d operator^(point3d CR p) const { return point3d{y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x}; }
  CEXP auto norm2() const { return x * x + y * y + z * z; }
  CEXP auto norm() const {
    static_assert(std::floating_point<FP>);
    return std::hypot(x, y, z);
  }
  CEXP point3d &do_unit() { return *this /= norm(); }
  CEXP point3d &do_rotx(FP theta) {
    const FP y0 = y, z0 = z, ct = std::cos(theta), st = std::sin(theta);
    return y = y0 * ct - z0 * st, z = y0 * st + z0 * ct, *this;
  }
  CEXP point3d &do_roty(FP theta) {
    const FP x0 = x, z0 = z, ct = std::cos(theta), st = std::sin(theta);
    return z = z0 * ct - x0 * st, x = z0 * st + x0 * ct, *this;
  }
  CEXP point3d &do_rotz(FP theta) {
    const FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    return x = x0 * ct - y0 * st, y = x0 * st + y0 * ct, *this;
  }
  CEXP point3d &do_rot(point3d e, FP theta) {
    e.do_unit();
    const FP a = e.x, b = e.y, c = e.z, x0 = x, y0 = y, z0 = z, ct = std::cos(theta), st = std::sin(theta);
    x = x0 * (ct + a * a * (1 - ct)) + y0 * (a * b * (1 - ct) - c * st) + z0 * (a * c * (1 - ct) + b * st);
    y = x0 * (a * b * (1 - ct) + c * st) + y0 * (ct + b * b * (1 - ct)) + z0 * (b * c * (1 - ct) - a * st);
    z = x0 * (a * c * (1 - ct) - b * st) + y0 * (b * c * (1 - ct) + a * st) + z0 * (ct + c * c * (1 - ct));
    return *this;
  }
};

}  // namespace tifa_libs::geo

#endif