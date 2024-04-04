#ifndef TIFALIBS_GRAPH_MANHATTAN_MST
#define TIFALIBS_GRAPH_MANHATTAN_MST

#include "../util/util.hpp"

namespace tifa_libs::graph {

//! USE Kruskal too get MST
// @return edges MAYBE in MST, {d(u, v), u, v}
template <class T>
requires std::is_signed_v<T>
auto manhattan_mst(vecpt<T> vp) {
  vecu id(vp.size());
  std::iota(id.begin(), id.end(), 0);
  vec<std::tuple<T, u32, u32>> ret;
  for (u32 k = 0; k < 4; ++k) {
    std::sort(id.begin(), id.end(), [&](u32 i, u32 j) { return vp[i].first + vp[i].second < vp[j].first + vp[j].second; });
    std::map<T, u32> mp;
    for (auto i : id) {
      for (auto it = mp.lower_bound(-vp[i].second); it != mp.end(); mp.erase(it++)) {
        u32 j = it->second;
        if (T x_ = vp[i].first - vp[j].first, y_ = vp[i].second - vp[j].second; y_ > x_) break;
        else ret.emplace_back(x_ + y_, i, j);
      }
      mp[-vp[i].second] = i;
    }
    for (auto& [x, y] : vp)
      if (k & 1) x *= -1;
      else std::swap(x, y);
  }
  return ret;
}

}  // namespace tifa_libs::graph

#endif