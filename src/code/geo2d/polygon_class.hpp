#ifndef TIFA_LIBS_GEO2D_POLYGON_CLASS
#define TIFA_LIBS_GEO2D_POLYGON_CLASS

#include "util.hpp"

#include "point.hpp"

namespace tifa_libs::geo2d {

template <class FP>
struct polygon {
  vec<point<FP>> vs;
  polygon() {}
  explicit polygon(size_t size_):
    vs(size_) {}
  explicit polygon(vec<point<FP>> const &vs_):
    vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, polygon &rhs) {
    for (auto &i : rhs.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, polygon const &rhs) {
    if (rhs.vs.empty()) return os;
    for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it) os << *it << ' ';
    return os << rhs.vs.back();
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

  auto circum() const {
    FP ret = dist_PP(vs.back(), vs.front());
    for (size_t i = 0; i < vs.size() - 1; ++i) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  }
  friend auto circum(const polygon &lhs) { return lhs.circum(); }
  auto area() const {
    FP ret = vs.back() ^ vs.front();
    for (size_t i = 0; i < vs.size() - 1; ++i) ret += vs[i] ^ vs[i + 1];
    return ret / 2;
  }
  friend auto area(const polygon &lhs) { return lhs.area(); }

  bool is_convex() const {
    bool flag[2] = {false, false};
    size_t sz = vs.size();
    if (sz < 3) return true;
    for (size_t i = 0, j = next(i), k = next(j); i < sz; ++i, j = next(j), k = next(k)) {
      auto sgn = sgn_cross(vs[i], vs[j], vs[k]);
      if (sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }

  // Count of integer point on the border of polygon
  u64 cnt_iP_border() {
    u64 ret = 0;
    for (size_t i = 0; i < vs.size(); ++i) ret += std::gcd(f2uint(std::abs(vs[i].x - vs[next(i)].x)), f2uint(std::abs(vs[i].y - vs[next(i)].y)));
    return ret;
  }
  // Count of integer point in the polygon, based on Pick theorem
  u64 cnt_iP_inner() { return f2uint(area()) - cnt_iP_border() / 2 + 1; }

  point<FP> mass_point() const {
    point<FP> ret{};
    FP area{};
    if (vs.size() == 0) return ret;
    if (vs.size() == 1) return vs[0];
    for (size_t i = 1; i < vs.size() - 1; ++i) {
      FP tmp = cross(vs[0], vs[i], vs[i + 1]);
      if (is_zero(tmp)) continue;
      area += tmp;
      ret += (vs[0] + vs[i] + vs[i + 1]) * (tmp / 3);
    }
    if (!is_zero(area)) ret = ret / area;
    return ret;
  }

  // simulated annealing
  template <class random_engine_t = std::default_random_engine, class temperature_t = double>
  point<FP> fermat_point(random_engine_t &engine, const temperature_t begin = 1e10, const temperature_t end = EPS, const temperature_t delta = .999) const {
    static std::uniform_real_distribution<temperature_t> u_angle(0, 2 * PI);
    point<FP> ret = vs.front(), pre = vs.front(), now;
    FP dis_ret{}, dis_pre{}, dis_now;
    for (size_t i = 1; i < vs.size(); ++i) dis_pre += dist_PP(vs[i], ret);
    dis_ret = dis_pre;
    for (temperature_t T = begin; T > end; T *= delta) {
      now = pre + make_P_polar(T, u_angle(engine));
      dis_now = 0;
      for (size_t i = 0; i < vs.size(); ++i) dis_now += dist_PP(vs[i], now);
      if (is_le(dis_now, dis_ret)) {
        ret = now;
        dis_ret = dis_now;
      }
      if (!is_ge(dis_now, dis_pre) || std::exp((dis_pre - dis_now) / T) > u_angle(engine) / u_angle.max()) {
        pre = now;
        dis_pre = dis_now;
      }
    }
    return ret;
  }
};

}  // namespace tifa_libs::geo2d

#endif