#ifndef TIFALIBS_GEO3D_POINT3D
#define TIFALIBS_GEO3D_POINT3D

#include "../util/traits_others.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point3d {
  using FP_t = FP;
  FP x, y, z;
  CEXP point3d() = default;
  CEXP point3d(FP x, FP y, FP z) NE : x{x}, y{y}, z{z} {}

  friend auto &operator>>(istream_c auto &is, point3d &p) NE { return is >> p.x >> p.y >> p.z; }
  friend auto &operator<<(ostream_c auto &os, point3d CR p) NE { return os << p.x << ' ' << p.y << ' ' << p.z; }
  // s + (t - s) * r
  template <std::floating_point T>
  friend CEXP point3d lerp(point3d CR s, point3d CR t, T r) NE { return s + (t - s) * r; }
  friend CEXP point3d mid_point(point3d CR s, point3d CR t) NE { return lerp(s, t, .5); }
  CEXP point3d &operator+=(FP n) NE {
    this->x += n, this->y += n, this->z += n;
    return *this;
  }
  CEXP point3d &operator-=(FP n) NE {
    this->x -= n, this->y -= n, this->z -= n;
    return *this;
  }
  CEXP point3d &operator*=(FP n) NE {
    this->x *= n, this->y *= n, this->z *= n;
    return *this;
  }
  CEXP point3d &operator/=(FP n) NE {
    this->x /= n, this->y /= n, this->z /= n;
    return *this;
  }
  CEXP point3d operator+(FP n) CNE { return point3d(*this) += n; }
  CEXP point3d operator-(FP n) CNE { return point3d(*this) -= n; }
  CEXP point3d operator*(FP n) CNE { return point3d(*this) *= n; }
  CEXP point3d operator/(FP n) CNE { return point3d(*this) /= n; }
  CEXP point3d &operator+=(point3d CR p) NE {
    this->x += p.x, this->y += p.y, this->z += p.z;
    return *this;
  }
  CEXP point3d &operator-=(point3d CR p) NE {
    this->x -= p.x, this->y -= p.y, this->z -= p.z;
    return *this;
  }
  CEXP point3d operator+(point3d CR p) CNE { return point3d(*this) += p; }
  CEXP point3d operator-(point3d CR p) CNE { return point3d(*this) -= p; }
  CEXP point3d operator-() CNE { return point3d{-x, -y, -z}; }
  CEXP auto operator<=>(point3d CR p) CNE {
    if (auto c = comp(x, p.x); c) return c;
    if (auto c = comp(y, p.y); c) return c;
    return comp(z, p.z);
  }
  CEXP bool operator==(point3d CR p) CNE { return (*this <=> p) == 0; }
  CEXP FP operator*(point3d CR p) CNE { return x * p.x + y * p.y + z * p.z; }
  CEXP point3d operator^(point3d CR p) CNE { return point3d{y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x}; }
  CEXP auto norm2() CNE { return x * x + y * y + z * z; }
  CEXP auto norm() CNE {
    static_assert(std::floating_point<FP>);
    return std::hypot(x, y, z);
  }
  CEXP point3d &do_unit() NE { return *this /= norm(); }
  CEXP point3d &do_rotx(FP theta) NE {
    const FP y0 = y, z0 = z, ct = std::cos(theta), st = std::sin(theta);
    y = y0 * ct - z0 * st, z = y0 * st + z0 * ct;
    return *this;
  }
  CEXP point3d &do_roty(FP theta) NE {
    const FP x0 = x, z0 = z, ct = std::cos(theta), st = std::sin(theta);
    z = z0 * ct - x0 * st, x = z0 * st + x0 * ct;
    return *this;
  }
  CEXP point3d &do_rotz(FP theta) NE {
    const FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    x = x0 * ct - y0 * st, y = x0 * st + y0 * ct;
    return *this;
  }
  CEXP point3d &do_rot(point3d e, FP theta) NE {
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