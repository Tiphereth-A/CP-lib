#ifndef TIFALIBS_GRAPH_TOPO_SORT
#define TIFALIBS_GRAPH_TOPO_SORT

#include "alist.hpp"

namespace tifa_libs::graph {

//! return empty vector if @fg is not DAG
template <bool with_deg>
constexpr vec<u32> topo_sort(alist<with_deg> const& fg) {
  u32 n = (u32)fg.g.size();
  vec<bool> vis(n), _(n);
  vec<u32> ans;
  auto dfs = [&](auto&& dfs, u32 i) -> bool {
    if (_[i]) return false;
    if (!vis[i]) {
      _[i] = true;
      for (u32 to : fg.g[i])
        if (!dfs(dfs, to)) return false;
      vis[i] = true;
      ans.push_back(i);
      _[i] = false;
    }
    return true;
  };
  for (u32 i = 0; i < n; ++i)
    if (!vis[i] && !dfs(dfs, i)) return {};
  std::reverse(ans.begin(), ans.end());
  return ans;
}

}  // namespace tifa_libs::graph

#endif