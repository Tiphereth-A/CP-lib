#ifndef TIFALIBS_GEO2D_POINT
#define TIFALIBS_GEO2D_POINT

#include "../util/func_fp.hpp"
#include "../util/traits_others.hpp"

namespace tifa_libs::geo {

template <class FP>
struct point {
  using FP_t = FP;

  FP x, y;
  CEXP point() = default;
  CEXP point(FP x, FP y) NE : x{x}, y{y} {}

  friend auto& operator>>(istream_c auto& is, point& p) NE { return is >> p.x >> p.y; }
  friend auto& operator<<(ostream_c auto& os, point CR p) NE { return os << p.x << ' ' << p.y; }
  // s + (t - s) * r
  template <std::floating_point T>
  friend CEXP point lerp(point CR s, point CR t, T r) NE { return s + (t - s) * r; }
  friend CEXP point mid_point(point CR s, point CR t) NE { return lerp(s, t, .5); }
  CEXP point& operator+=(arithm_c auto n) NE {
    this->x += n, this->y += n;
    return *this;
  }
  CEXP point& operator-=(arithm_c auto n) NE {
    this->x -= n, this->y -= n;
    return *this;
  }
  CEXP point& operator*=(arithm_c auto n) NE {
    this->x *= n, this->y *= n;
    return *this;
  }
  CEXP point& operator/=(arithm_c auto n) NE {
    this->x /= n, this->y /= n;
    return *this;
  }
  friend CEXP point operator+(point x, arithm_c auto n) NE { return x += n; }
  friend CEXP point operator+(arithm_c auto n, point x) NE { return x += n; }
  friend CEXP point operator-(point x, arithm_c auto n) NE { return x -= n; }
  friend CEXP point operator-(arithm_c auto n, point x) NE { return x -= n; }
  friend CEXP point operator*(point x, arithm_c auto n) NE { return x *= n; }
  friend CEXP point operator*(arithm_c auto n, point x) NE { return x *= n; }
  friend CEXP point operator/(point x, arithm_c auto n) NE { return x /= n; }
  friend CEXP point operator/(arithm_c auto n, point x) NE { return x /= n; }
  CEXP point& operator+=(point CR p) NE {
    this->x += p.x, this->y += p.y;
    return *this;
  }
  CEXP point& operator-=(point CR p) NE {
    this->x -= p.x, this->y -= p.y;
    return *this;
  }
  CEXP point operator+(point CR p) CNE { return point(*this) += p; }
  CEXP point operator-(point CR p) CNE { return point(*this) -= p; }
  CEXP point operator-() CNE { return point{-x, -y}; }
  CEXP auto operator<=>(point CR p) CNE {
    if (auto CR c = comp(x, p.x); c) return c;
    return comp(y, p.y);
  }
  CEXP bool operator==(point CR p) CNE { return (*this <=> p) == 0; }
  CEXP FP operator*(point CR p) CNE { return x * p.x + y * p.y; }
  CEXP FP operator^(point CR p) CNE { return x * p.y - y * p.x; }
  CEXP FP arg() CNE {
    static_assert(std::is_floating_point_v<FP>);
    return std::atan2(y, x);
  }
  CEXP FP arg_2pi() CNE {
    FP res = arg();
    retif_((is_neg(res)), res + 2 * pi_v<FP>, res);
  }
  CEXP FP norm2() CNE { return x * x + y * y; }
  CEXP FP norm() CNE {
    static_assert(std::is_floating_point_v<FP>);
    return std::hypot(x, y);
  }
  CEXP point& do_unit() NE {
    static_assert(std::is_floating_point_v<FP>);
    return *this /= norm();
  }
  static CEXP u32 QUAD__[9] = {6, 7, 8, 5, 0, 1, 4, 3, 2};
  // 4 3 2
  // 5 0 1
  // 6 7 8
  CEXP u32 quad() CNE { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }
  CEXP int toleft(point CR p) CNE { return sgn(*this ^ p); }
  CEXP point& do_rot(FP theta) NE {
    const FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    x = x0 * ct - y0 * st, y = x0 * st + y0 * ct;
    return *this;
  }
  friend CEXP point rot(point p, FP theta) NE { return p.do_rot(theta); }
  CEXP point& do_rot90() NE {
    const FP _ = x;
    x = -y, y = _;
    return *this;
  }
  friend CEXP point rot90(point p) NE { return p.do_rot90(); }
  CEXP point& do_rot270() NE {
    const FP _ = y;
    y = -x, x = _;
    return *this;
  }
  friend CEXP point rot270(point p) NE { return p.do_rot270(); }
};

}  // namespace tifa_libs::geo

#endif