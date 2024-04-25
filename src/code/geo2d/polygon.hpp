#ifndef TIFALIBS_GEO2D_POLYGON
#define TIFALIBS_GEO2D_POLYGON

#include "../edh/discretization.hpp"
#include "cross.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

template <class FP>
struct polygon {
  vec<point<FP>> vs;

  CEXP polygon() {}
  explicit CEXP polygon(u32 sz) : vs(sz) {}
  explicit CEXP polygon(vec<point<FP>> CR vs_) : vs(vs_) {}

  friend std::istream &operator>>(std::istream &is, polygon &p) {
    for (auto &i : p.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, polygon CR p) {
    if (p.vs.empty()) return os;
    for (auto it = p.vs.begin(); it != p.vs.end() - 1; ++it) os << *it << ' ';
    return os << p.vs.back();
  }
  CEXP point<FP> &operator[](u32 x) { return vs[x]; }
  CEXP point<FP> CR operator[](u32 x) const { return vs[x]; }

  CEXP polygon &resort() {
    std::ranges::sort(vs);
    return *this;
  }
  CEXP polygon &reunique() {
    vs = uniq(vs);
    return *this;
  }

  CEXP auto prev(TPN vec<point<FP>>::const_iterator it) const { return --(it == vs.begin() ? it = vs.end() : it); }
  CEXP auto next(TPN vec<point<FP>>::const_iterator it) const { return ++it == vs.end() ? vs.begin() : it; }
  CEXP u32 prev(u32 idx) const { return idx == 0 ? (u32)vs.size() - 1 : idx - 1; }
  CEXP u32 next(u32 idx) const { return idx + 1 == (u32)vs.size() ? 0 : idx + 1; }

  CEXP FP circum() const {
    FP ret = dist_PP(vs.back(), vs.front());
    for (u32 i = 0; i < (u32)vs.size() - 1; ++i) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  }
  CEXP FP area() const {
    if (vs.size() < 3) return 0;
    FP ret = vs.back() ^ vs.front();
    for (u32 i = 0; i < (u32)vs.size() - 1; ++i) ret += vs[i] ^ vs[i + 1];
    return ret / 2;
  }
  CEXP bool is_convex() const {
    bool flag[2] = {false, false};
    u32 n = (u32)vs.size();
    if (n < 3) return true;
    for (u32 i = 0, j = next(i), k = next(j); i < n; ++i, j = next(j), k = next(k)) {
      auto sgn = sgn_cross(vs[i], vs[j], vs[k]);
      if (sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }
};

}  // namespace tifa_libs::geo

#endif