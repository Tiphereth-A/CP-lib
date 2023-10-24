#ifndef TIFA_LIBS_GRAPH_PATH
#define TIFA_LIBS_GRAPH_PATH

#include "adjlist.hpp"

namespace tifa_libs::graph {

template <class T>
std::optional<vec<u32>> path(adjlist<T> const &g, u32 from, u32 to) {
  vec<u32> ret;
  bool failed = true;
  auto dfs = [&](auto &&dfs, u32 now, u32 fa) -> void {
    ret.push_back(now);
    if (now == to) {
      failed = false;
      return;
    }
    for (auto dst : g[now]) {
      if (dst.to == fa) continue;
      dfs(dfs, dst.to, now);
      if (!failed) return;
    }
    if (!failed) return;
    ret.pop_back();
  };
  dfs(dfs, from, g.v_size());
  if (failed) return {};
  return ret;
}

}  // namespace tifa_libs::graph

#endif