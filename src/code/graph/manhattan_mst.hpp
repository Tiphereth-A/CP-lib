#ifndef TIFALIBS_GRAPH_MANHATTAN_MST
#define TIFALIBS_GRAPH_MANHATTAN_MST

#include "../util/alias_others.hpp"

namespace tifa_libs::graph {

//! USE Kruskal too get MST
// @return edges MAYBE in MST, {d(u, v), u, v}
template <class T>
requires std::is_signed_v<T>
vec<edge_t<T>> manhattan_mst(vecpt<T> vp) NE {
  vecu id(vp.size());
  std::iota(id.begin(), id.end(), 0);
  vec<edge_t<T>> ret;
  flt_ (u32, k, 0, 4) {
    sort(id, {}, [&](u32 i) NE { return vp[i].first + vp[i].second; });
    for (map<T, u32> mp; auto i : id) {
      for (auto it = mp.lower_bound(-vp[i].second); it != mp.end(); mp.erase(it++)) {
        u32 j = it->second;
        if (T x_ = vp[i].first - vp[j].first, y_ = vp[i].second - vp[j].second; y_ > x_) break;
        else ret.emplace_back(x_ + y_, i, j);
      }
      mp[-vp[i].second] = i;
    }
    for (auto& [x, y] : vp)
      if (k & 1) x *= -1;
      else swap(x, y);
  }
  return ret;
}

}  // namespace tifa_libs::graph

#endif