#ifndef TIFALIBS_GEO2D_POLYGON
#define TIFALIBS_GEO2D_POLYGON

#include "cross.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

template <class FP>
struct polygon {
  vec<point<FP>> vs;

  polygon() {}
  explicit polygon(u32 sz) : vs(sz) {}
  explicit polygon(vec<point<FP>> const &vs_) : vs(vs_) {}

  friend std::istream &operator>>(std::istream &is, polygon &p) {
    for (auto &i : p.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, polygon const &p) {
    if (p.vs.empty()) return os;
    for (auto it = p.vs.begin(); it != p.vs.end() - 1; ++it) os << *it << ' ';
    return os << p.vs.back();
  }
  point<FP> &operator[](u32 x) { return vs[x]; }
  point<FP> const &operator[](u32 x) const { return vs[x]; }

  polygon &resort() {
    std::sort(vs.begin(), vs.end());
    return *this;
  }
  polygon &reunique() {
    resort();
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    return *this;
  }

  auto prev(typename vec<point<FP>>::const_iterator it) const { return --(it == vs.begin() ? it = vs.end() : it); }
  auto next(typename vec<point<FP>>::const_iterator it) const { return ++it == vs.end() ? vs.begin() : it; }
  u32 prev(u32 idx) const { return idx == 0 ? (u32)vs.size() - 1 : idx - 1; }
  u32 next(u32 idx) const { return idx + 1 == (u32)vs.size() ? 0 : idx + 1; }

  FP circum() const {
    FP ret = dist_PP(vs.back(), vs.front());
    for (u32 i = 0; i < (u32)vs.size() - 1; ++i) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  }
  FP area() const {
    if (vs.size() < 3) return 0;
    FP ret = vs.back() ^ vs.front();
    for (u32 i = 0; i < (u32)vs.size() - 1; ++i) ret += vs[i] ^ vs[i + 1];
    return ret / 2;
  }
  bool is_convex() const {
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