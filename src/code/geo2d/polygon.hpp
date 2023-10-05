#ifndef TIFA_LIBS_GEO2D_POLYGON
#define TIFA_LIBS_GEO2D_POLYGON

#include "cross.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

template <class FP>
struct polygon {
  vec<point<FP>> vs;
  polygon() {}
  explicit polygon(size_t sz):
    vs(sz) {}
  explicit polygon(vec<point<FP>> const &vs_):
    vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, polygon &p) {
    for (auto &i : p.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, polygon const &p) {
    if (p.vs.empty()) return os;
    for (auto it = p.vs.begin(); it != p.vs.end() - 1; ++it) os << *it << ' ';
    return os << p.vs.back();
  }

  polygon &resort() {
    std::sort(vs.begin(), vs.end());
    return *this;
  }
  void resort_in_clockwise() {
    std::sort(vs.begin(), vs.end(), [](point<FP> const &lhs, point<FP> const &rhs) { return lhs.quad() == rhs.quad() ? is_neg(lhs ^ rhs) : lhs.quad() > rhs.quad(); });
  }
  void resort_in_counterclockwise() {
    std::sort(vs.begin(), vs.end(), [](point<FP> const &lhs, point<FP> const &rhs) { return lhs.quad() == rhs.quad() ? is_pos(lhs ^ rhs) : lhs.quad() < rhs.quad(); });
  }
  polygon &reunique() {
    resort();
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    return *this;
  }

  point<FP> &operator[](size_t x) { return vs[x]; }
  point<FP> const &operator[](size_t x) const { return vs[x]; }

  auto prev(typename vec<point<FP>>::const_iterator it) const { return --(it == vs.begin() ? it = vs.end() : it); }
  auto next(typename vec<point<FP>>::const_iterator it) const { return ++it == vs.end() ? vs.begin() : it; }
  size_t prev(size_t idx) const { return idx == 0 ? vs.size() - 1 : idx - 1; }
  size_t next(size_t idx) const { return idx + 1 == vs.size() ? 0 : idx + 1; }

  FP circum() const {
    FP ret = dist_PP(vs.back(), vs.front());
    for (size_t i = 0; i < vs.size() - 1; ++i) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  }
  FP area() const {
    if (vs.size() < 3) return 0;
    FP ret = vs.back() ^ vs.front();
    for (size_t i = 0; i < vs.size() - 1; ++i) ret += vs[i] ^ vs[i + 1];
    return ret / 2;
  }

  bool is_convex() const {
    bool flag[2] = {false, false};
    size_t n = vs.size();
    if (n < 3) return true;
    for (size_t i = 0, j = next(i), k = next(j); i < n; ++i, j = next(j), k = next(k)) {
      auto sgn = sgn_cross(vs[i], vs[j], vs[k]);
      if (sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }
};

}  // namespace tifa_libs::geo

#endif