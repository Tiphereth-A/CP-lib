#ifndef TIFALIBS_GEO2D_MIN_DIS_PS
#define TIFALIBS_GEO2D_MIN_DIS_PS

#include "dist_pp.hpp"

namespace tifa_libs::geo {

//! the distance is |.|^2 if FP is not floating point
// @return indexes of the closest points
template <class FP>
CEXP pttu min_dis_Ps(vec<point<FP>> CR vp) NE {
  const u32 n = (u32)vp.size();
  using T = std::pair<point<FP>, u32>;
  auto dis1 = [](FP x) NE {
    if CEXP (std::floating_point<FP>) return abs(x);
    else return x * x;
  };
  vec<T> vpi;
  vpi.reserve(n);
  flt_ (u32, i, 0, n) vpi.emplace_back(vp[i], i);
  sort(vpi);
  FP d = std::numeric_limits<FP>::max();
  u32 a = -1_u32, b = -1_u32;
  auto upd = [&](T CR x, T CR y) NE {
    FP _;
    if CEXP (std::floating_point<FP>) _ = dist_PP(x.first, y.first);
    else _ = (x.first - y.first).norm2();
    if (is_lt(_, d)) d = _, a = x.second, b = y.second;
  };
  std::multiset<T, decltype([](T CR l, T CR r) NE { return is_lt(l.first.y, r.first.y); })> st;
  std::vector<TPN decltype(st)::const_iterator> qt(n);
  for (u32 i = 0, r = 0; i < n; ++i) {
    auto& p = vpi[i];
    while (r < i && !is_lt(dis1(vpi[r].first.x - p.first.x), d)) st.erase(qt[r++]);
    auto it2 = st.upper_bound(p), it = it2;
    if (it != st.begin())
      for (auto _ = std::prev(it); upd(*_, p), (_ != st.begin() && is_lt(dis1(p.first.y - _->first.y), d)); --_);
    for (; it != st.end() && is_lt(dis1(it->first.y - p.first.y), d); upd(*it++, p));
    qt[i] = st.emplace_hint(it2, p);
  }
  return {a, b};
}

}  // namespace tifa_libs::geo

#endif