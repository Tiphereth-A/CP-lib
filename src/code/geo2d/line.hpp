#ifndef TIFALIBS_GEO2D_LINE
#define TIFALIBS_GEO2D_LINE

#include "cross.hpp"

namespace tifa_libs::geo {

template <class FP>
struct line {
  point<FP> l, r;
  CEXP line() {}
  CEXP line(point<FP> CR s, point<FP> CR t) : l(s), r(t) {}
  CEXP line(point<FP> CR s, FP angle_x) : l(s), r(s + is_eq(angle_x, pi_v<FP> / 2) ? point<FP>{0, 1} : point<FP>{1, std::tan(angle_x)}) { assert(angle_x > 0 && angle_x < pi_v<FP>); }
  // ax + by + c = 0
  CEXP line(FP a, FP b, FP c) {
    if (is_zero(a)) l = {0, -c / b}, r = {1, -c / b};
    else if (is_zero(b)) l = {-c / a, 0}, r = {-c / a, 1};
    else l = {0, -c / b}, r = {1, -(c + a) / b};
  }
  CEXP line(FP s_x, FP s_y, FP t_x, FP t_y) : l(s_x, s_y), r(t_x, t_y) {}

  friend std::istream& operator>>(std::istream& is, line& l) { return is >> l.l >> l.r; }
  friend std::ostream& operator<<(std::ostream& os, line CR l) { return os << l.l << ' ' << l.r; }

  CEXP point<FP> direction() const { return r - l; }
  CEXP bool is_parallel(line CR r) const { return is_zero(direction() ^ r.direction()); }
  friend CEXP bool is_parallel(line CR l, line CR r) { return l.is_parallel(r); }
  CEXP bool is_same_dir(line CR r) const { return is_parallel(r) && is_pos(direction() * r.direction()); }
  friend CEXP bool is_same_dir(line CR l, line CR r) { return l.is_same_dir(r); }

  friend CEXP bool operator==(line CR l, line CR r) { return l.l == r.l && l.r == r.r; }
  friend CEXP auto operator<=>(line CR l, line CR r) {
    if (l == r) return 0;
    if (l.is_same_dir(r)) return r.is_include_strict(l.l) ? -1 : 1;
    const auto vl = l.direction(), vr = r.direction();
    if (vl.quad() != vr.quad()) return (i32)vl.quad() - (i32)vr.quad();
    return -sgn(vl ^ vr);
  }

  CEXP int toleft(point<FP> CR p) const { return sgn_cross(l, r, p); }
  // half plane
  CEXP bool is_include_strict(point<FP> CR p) const { return toleft(p) > 0; }
  // half plane
  CEXP bool is_include(point<FP> CR p) const { return toleft(p) >= 0; }

  // translate @dist along the direction of half plane
  CEXP line& do_push(FP dist) {
    const point delta = direction().do_rot90().do_unit() * dist;
    l += delta, r += delta;
    return *this;
  }
};

}  // namespace tifa_libs::geo

#endif