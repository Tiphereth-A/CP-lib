#ifndef TIFALIBS_GEO2D_POLYGON
#define TIFALIBS_GEO2D_POLYGON

#include "../edh/discretization.hpp"
#include "../math/kahan.hpp"
#include "cross.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

template <class FP>
struct polygon {
  vec<point<FP>> vs;

  CEXP polygon() {}
  explicit CEXP polygon(u32 sz) : vs(sz) {}
  CEXP polygon(itl<point<FP>> vs_) : vs(vs_) {}
  CEXP polygon(spn<point<FP>> vs_) : vs(vs_.begin(), vs_.end()) {}

  friend std::istream &operator>>(std::istream &is, polygon &p) {
    for (auto &i : p.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, polygon CR p) {
    if (p.vs.empty()) return os;
    for (auto it = p.vs.begin(); it != p.vs.end() - 1; ++it) os << *it << ' ';
    return os << p.vs.back();
  }
  CEXP u32 size() const { return (u32)vs.size(); }
  CEXP point<FP> &operator[](u32 x) { return vs[x]; }
  CEXP point<FP> CR operator[](u32 x) const { return vs[x]; }
  CEXP polygon &resort() { return std::ranges::sort(vs), *this; }
  CEXP polygon &reunique() { return vs = uniq(vs), *this; }
  CEXP auto prev(TPN vec<point<FP>>::const_iterator it) const { return --(it == vs.begin() ? it = vs.end() : it); }
  CEXP auto next(TPN vec<point<FP>>::const_iterator it) const { return ++it == vs.end() ? vs.begin() : it; }
  CEXP u32 prev(u32 idx) const { return idx == 0 ? size() - 1 : idx - 1; }
  CEXP u32 next(u32 idx) const { return idx + 1 == size() ? 0 : idx + 1; }
  CEXP FP circum() const {
    math::kahan<FP> ret = dist_PP(vs.back(), vs.front());
    flt_ (u32, i, 0, size() - 1) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  }
  CEXP FP area2() const {
    if (size() < 3) return 0;
    math::kahan<FP> ret = vs.back() ^ vs.front();
    flt_ (u32, i, 0, size() - 1) ret += vs[i] ^ vs[i + 1];
    return ret;
  }
  CEXP FP area() const {
    static_assert(std::floating_point<FP>);
    return area2() * (FP).5;
  }
  CEXP bool is_convex() const {
    bool flag[2] = {false, false};
    const u32 n = size();
    if (n < 3) return true;
    for (u32 i = 0, j = next(i), k = next(j); i < n; ++i, j = next(j), k = next(k)) {
      if (auto sgn = sgn_cross(vs[i], vs[j], vs[k]); sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }
  // @return nullopt if @p on board of polygon, otherwise winding number
  CEXP std::optional<u32> winding(point<FP> CR p) const {
    u32 cnt = 0;
    flt_ (u32, i, 0, size()) {
      auto &&u = vs[i], &&v = vs[next(i)];
      if (!sgn_cross(p, u, v) && !sgn_dot(p, u, v)) return {};
      if (is_zero(u.y - v.y)) continue;
      if (is_lt(u.y, v.y) && !is_pos(u, v, p)) continue;
      if (is_gt(u.y, v.y) && !is_neg(u, v, p)) continue;
      if (is_lt(u.y, p.y) && !is_lt(v.y, p.y)) ++cnt;
      if (!is_lt(u.y, p.y) && is_lt(v.y, p.y)) --cnt;
    }
    return cnt;
  }
};

}  // namespace tifa_libs::geo

#endif