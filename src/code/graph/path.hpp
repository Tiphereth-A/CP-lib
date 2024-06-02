#ifndef TIFALIBS_GRAPH_PATH
#define TIFALIBS_GRAPH_PATH

#include "alist.hpp"

namespace tifa_libs::graph {

template <class G>
CEXP std::optional<vecu> path(G CR g, u32 from, u32 to) {
  vecu ret;
  bool failed = true;
  auto dfs = [&](auto &&dfs, u32 now, u32 fa) -> void {
    ret.push_back(now);
    if (now == to) return void(failed = false);
    for (auto v : g.g[now]) {
      u32 to = 0;
      if CEXP (is_alist<G>) to = v;
      else to = v.first;
      if (to == fa) continue;
      if (dfs(dfs, to, now); !failed) return;
    }
    if (!failed) return;
    ret.pop_back();
  };
  if (dfs(dfs, from, -1_u32); failed) return {};
  return ret;
}

}  // namespace tifa_libs::graph

#endif