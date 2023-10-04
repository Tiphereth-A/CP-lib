#ifndef TIFA_LIBS_GEO2D_POINT
#define TIFA_LIBS_GEO2D_POINT

#include "point_class.hpp"

namespace tifa_libs::geo2d {

template <class FP>
constexpr point<FP> make_P_polar(FP r, FP theta) { return point{r * std::cos(theta), r * std::sin(theta)}; }

// distance of two points (Euclidian)
template <class FP>
constexpr FP dist_PP(point<FP> const &lhs, point<FP> const &rhs) { return std::hypot(lhs.x - rhs.x, lhs.y - rhs.y); }
// distance of two points (Manhattan)
template <class FP>
constexpr FP dist_MaPP(point<FP> const &lhs, point<FP> const &rhs) { return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y); }
// distance of two points (Chebyshev)
template <class FP>
constexpr FP dist_ChPP(point<FP> const &lhs, point<FP> const &rhs) { return std::max(std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y)); }

// (p2 - p1) ^  (p3 - p1)
template <class FP>
constexpr FP cross(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y); }
template <class FP>
constexpr int sgn_cross(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return sgn(cross(p1, p2, p3)); }

// (p2 - p1) * (p3 - p1)
template <class FP>
constexpr FP dot(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y); }
template <class FP>
constexpr int sgn_dot(point<FP> const &p1, point<FP> const &p2, point<FP> const &p3) { return sgn(dot(p1, p2, p3)); }

//! containing endpoints
template <class FP>
constexpr bool is_in_middle(point<FP> a, point<FP> m, point<FP> b) { return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y); }

// clamp angle of two points
template <class FP>
constexpr FP ang_PP(point<FP> const &p1, point<FP> const &p2) { return std::atan2(p1 ^ p2, p1 * p2); }
// clamp angle of two points, result in [0,2 pi)
template <class FP>
constexpr FP ang2pi_PP(point<FP> const &p1, point<FP> const &p2) {
  FP res = ang_PP(p1, p2);
  return is_neg(res) ? res + 2 * PI : res;
}

// min distance of a set of points
//! need to sort `vp` first by the ascending order of x
template <class FP>
FP min_dist_Ps(vec<point<FP>> const &vp, size_t l, size_t r) {
  FP ret = std::numeric_limits<FP>::max();
  if (r - l <= 5) {
    for (size_t i = l; i < r; ++i)
      for (size_t j = l; j < i; ++j) ret = std::min(ret, dist_PP(vp[i], vp[j]));
    return ret;
  }
  size_t mid = r - (r - l) / 2;
  ret = std::min(min_dist_Ps(vp, l, mid), min_dist_Ps(vp, mid, r));
  vec<point<FP>> q;
  for (size_t i = l; i < r; ++i)
    if (std::abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
  std::stable_sort(q.begin(), q.end(), [](auto const &lhs, auto const &rhs) -> bool { return lhs.y < rhs.y; });
  for (size_t i = 1; i < q.size(); ++i)
    for (size_t j = i - 1; ~j && q[j].y >= q[i].y - ret; --j) ret = std::min(ret, dist_PP(q[i], q[j]));
  return ret;
}

// max number of points covered by a circle with radius @r
template <class FP>
u64 max_cover_Ps(vec<point<FP>> const &vp, const FP r) {
  if (is_neg(r)) return 0;
  if (is_zero(r)) return 1;
  const FP diam = r * 2;
  u64 ans = 1;
  vec<std::pair<FP, i64>> angles;
  FP dist;
  for (size_t i = 0; i < vp.size(); ++i) {
    angles.clear();
    for (size_t j = 0; j < vp.size(); ++j) {
      if (i == j || is_ge(dist = dist_PP(vp[i], vp[j]), diam)) continue;
      FP delta = std::acos(dist / diam), polar = ang2pi_PP(vp[i], vp[j]);
      angles.emplace_back(polar - delta, 1);
      angles.emplace_back(polar + delta, -1);
    }
    std::sort(angles.begin(), angles.end());
    u64 sum = 0;
    for (size_t j = 0; j < angles.size(); ++j) ans = std::max(ans, sum += angles[j].second);
  }
  return ans;
}

}  // namespace tifa_libs::geo2d

#endif