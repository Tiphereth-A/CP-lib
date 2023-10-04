#ifndef TIFA_LIBS_GEO2D_LINE
#define TIFA_LIBS_GEO2D_LINE

#include "cross.hpp"

namespace tifa_libs::geo2d {

template <class FP>
struct line {
  point<FP> l, r;
  line() {}
  constexpr line(point<FP> const &start_, point<FP> const &end_):
    l(start_), r(end_) {}
  constexpr line(const FP &start_x, const FP &start_y, const FP &end_x, const FP &end_y):
    l(start_x, start_y), r(end_x, end_y) {}
  friend std::istream &operator>>(std::istream &is, line &rhs) { return is >> rhs.l >> rhs.r; }
  friend std::ostream &operator<<(std::ostream &os, line const &rhs) { return os << rhs.l << ' ' << rhs.r; }

  constexpr point<FP> direction() const { return r - l; }

  constexpr auto is_parallel(line const &rhs) const { return is_zero(direction() ^ rhs.direction()); }
  friend constexpr auto is_parallel(line const &lhs, line const &rhs) { return lhs.is_parallel(rhs); }

  constexpr auto is_same_dir(line const &rhs) const { return is_parallel(rhs) && is_pos(direction() * rhs.direction()); }
  friend constexpr auto is_same_dir(line const &lhs, line const &rhs) { return lhs.is_same_dir(rhs); }

  constexpr friend bool operator<(line const &lhs, line const &rhs) {
    if (lhs.is_same_dir(rhs)) return rhs.is_include_strict(lhs.l);
    auto vl = lhs.direction(), vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_pos(vl ^ vr);
  }
  friend bool operator==(line const &lhs, line const &rhs) { return lhs.l == rhs.l && lhs.r == rhs.r; }

  constexpr auto slope() const { return (r.y - l.y) / (r.x - l.x); }
  friend constexpr auto slope(line const &lhs) { return lhs.slope(); }

  constexpr auto slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  friend constexpr auto slope_inv(line const &lhs) { return lhs.slope_inv(); }

  constexpr auto intercept_v() const { return r.y - r.x * slope(); }
  friend constexpr auto intercept_v(line const &lhs) { return lhs.intercept_v(); }

  constexpr auto intercept_h() const { return r.x - r.y * slope_inv(); }
  friend constexpr auto intercept_h(line const &lhs) { return lhs.intercept_h(); }

  constexpr auto lerp_y(FP x) const { return l.y + (x - l.x) * slope(); }
  friend constexpr auto lerp_y(line const &lhs, FP x) { return lhs.lerp_y(x); }

  constexpr auto lerp_x(FP y) const { return l.x + (y - l.y) * slope_inv(); }
  friend constexpr auto lerp_x(line const &lhs, FP y) { return lhs.lerp_x(y); }

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
  friend constexpr line push(line lhs, FP dist) { return lhs.do_push(dist); }
};

}  // namespace tifa_libs::geo2d

#endif