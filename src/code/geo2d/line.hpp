#ifndef TIFALIBS_GEO2D_LINE
#define TIFALIBS_GEO2D_LINE

#include "cross.hpp"

namespace tifa_libs::geo {

template <class FP>
struct line {
  point<FP> l, r;
  constexpr line() {}
  constexpr line(point<FP> const &s, point<FP> const &t) : l(s), r(t) {}
  constexpr line(point<FP> const &s, FP angle_x) : l(s), r(s + is_eq(angle_x, pi_v<FP> / 2) ? point<FP>{0, 1} : point<FP>{1, std::tan(angle_x)}) { assert(angle_x > 0 && angle_x < pi_v<FP>); }
  // ax + by + c = 0
  constexpr line(FP a, FP b, FP c) {
    if (is_zero(a)) l = {0, -c / b}, r = {1, -c / b};
    else if (is_zero(b)) l = {-c / a, 0}, r = {-c / a, 1};
    else l = {0, -c / b}, r = {1, -(c + a) / b};
  }
  constexpr line(FP s_x, FP s_y, FP t_x, FP t_y) : l(s_x, s_y), r(t_x, t_y) {}

  friend std::istream &operator>>(std::istream &is, line &l) { return is >> l.l >> l.r; }
  friend std::ostream &operator<<(std::ostream &os, line const &l) { return os << l.l << ' ' << l.r; }

  constexpr point<FP> direction() const { return r - l; }
  constexpr bool is_parallel(line const &r) const { return is_zero(direction() ^ r.direction()); }
  friend constexpr bool is_parallel(line const &l, line const &r) { return l.is_parallel(r); }
  constexpr bool is_same_dir(line const &r) const { return is_parallel(r) && is_pos(direction() * r.direction()); }
  friend constexpr bool is_same_dir(line const &l, line const &r) { return l.is_same_dir(r); }

  friend constexpr bool operator==(line const &l, line const &r) { return l.l == r.l && l.r == r.r; }
  friend constexpr auto operator<=>(line const &l, line const &r) {
    if (l == r) return 0;
    if (l.is_same_dir(r)) return r.is_include_strict(l.l) ? -1 : 1;
    auto vl = l.direction(), vr = r.direction();
    if (vl.quad() != vr.quad()) return (i32)vl.quad() - (i32)vr.quad();
    return -sgn(vl ^ vr);
  }

  // half plane
  constexpr bool is_include_strict(point<FP> const &p) const { return is_pos(cross(l, r, p)); }
  // half plane
  constexpr bool is_include(point<FP> const &p) const { return !is_neg(cross(l, r, p)); }

  // translate @dist along the direction of half plane
  constexpr line &do_push(FP dist) {
    point delta = direction().do_rot90().do_unit() * dist;
    l += delta;
    r += delta;
    return *this;
  }
};

}  // namespace tifa_libs::geo

#endif