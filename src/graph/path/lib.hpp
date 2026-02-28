#ifndef TIFALIBS_GRAPH_PATH_LIB
#define TIFALIBS_GRAPH_PATH_LIB

#include "../../util/alias/others/lib.hpp"
#include "../../util/traits/graph/lib.hpp"

namespace tifa_libs::graph {

template <alist_c G>
CEXP auto path(G CR g, u32 from, u32 to) NE {
  std::optional ret{vecu{}};
  bool failed = true;
  auto dfs = [&](auto&& dfs, u32 now, u32 fa) NE -> void {
    ret->push_back(now);
    if (now == to) {
      failed = false;
      return;
    }
    if CEXP (alistw_c<G>)
      for (auto&& [v, w] : g[now]) {
        u32 to = 0;
        if ((to = v) == fa) continue;
        if (dfs(dfs, to, now); !failed) return;
      }
    else
      for (auto v : g[now]) {
        u32 to = 0;
        if ((to = (u32)v) == fa) continue;
        if (dfs(dfs, to, now); !failed) return;
      }
    if (!failed) return;
    ret->pop_back();
  };
  if (dfs(dfs, from, -1_u32); failed) ret = std::nullopt;
  return ret;
}

}  // namespace tifa_libs::graph

#endif