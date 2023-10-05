#ifndef TIFA_LIBS_GEO2D_LINE
#define TIFA_LIBS_GEO2D_LINE

#include "cross.hpp"

namespace tifa_libs::geo {

template <class FP>
struct line {
  point<FP> l, r;
  line() {}
  constexpr line(point<FP> const &s, point<FP> const &t):
    l(s), r(t) {}
  constexpr line(FP s_x, FP s_y, FP t_x, FP t_y):
    l(s_x, s_y), r(t_x, t_y) {}
  friend std::istream &operator>>(std::istream &is, line &l) { return is >> l.l >> l.r; }
  friend std::ostream &operator<<(std::ostream &os, line const &l) { return os << l.l << ' ' << l.r; }

  constexpr point<FP> direction() const { return r - l; }

  constexpr auto is_parallel(line const &r) const { return is_zero(direction() ^ r.direction()); }
  friend constexpr auto is_parallel(line const &l, line const &r) { return l.is_parallel(r); }

  constexpr auto is_same_dir(line const &r) const { return is_parallel(r) && is_pos(direction() * r.direction()); }
  friend constexpr auto is_same_dir(line const &l, line const &r) { return l.is_same_dir(r); }

  constexpr friend bool operator<(line const &l, line const &r) {
    if (l.is_same_dir(r)) return r.is_include_strict(l.l);
    auto vl = l.direction(), vr = r.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_pos(vl ^ vr);
  }
  friend bool operator==(line const &l, line const &r) { return l.l == r.l && l.r == r.r; }

  constexpr auto slope() const { return (r.y - l.y) / (r.x - l.x); }
  friend constexpr auto slope(line const &l) { return l.slope(); }

  constexpr auto slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  friend constexpr auto slope_inv(line const &l) { return l.slope_inv(); }

  constexpr auto intercept_v() const { return r.y - r.x * slope(); }
  friend constexpr auto intercept_v(line const &l) { return l.intercept_v(); }

  constexpr auto intercept_h() const { return r.x - r.y * slope_inv(); }
  friend constexpr auto intercept_h(line const &l) { return l.intercept_h(); }

  constexpr auto lerp_y(FP x) const { return l.y + (x - l.x) * slope(); }
  friend constexpr auto lerp_y(line const &l, FP x) { return l.lerp_y(x); }

  constexpr auto lerp_x(FP y) const { return l.x + (y - l.y) * slope_inv(); }
  friend constexpr auto lerp_x(line const &l, FP y) { return l.lerp_x(y); }

  // half plane
  constexpr bool is_include_strict(point<FP> const &p) const { return is_pos(cross(l, r, p)); }
  // half plane
  constexpr bool is_include(point<FP> const &p) const { return !is_neg(cross(l, r, p)); }

  // translate @dist along the direction of half plane
  constexpr line &do_push(FP dist) {
    point delta = direction().do_rot90().do_unit();
    delta *= dist;
    l += delta;
    r += delta;
    return *this;
  }
  // translate @dist along the direction of half plane
  friend constexpr line push(line l, FP dist) { return l.do_push(dist); }
};

}  // namespace tifa_libs::geo

#endif