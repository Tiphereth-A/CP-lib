#pragma once

#include "../ds/graph_c/lib.hpp"

namespace tifa_libs {

template <graph_c G>
CEXP auto path(G CR g, u32 from, u32 to) NE {
  std::optional ret{vecu{}};
  bool failed = true;
  auto dfs = [&](auto&& dfs, u32 now, u32 fa) NE -> void {
    ret->push_back(now);
    if (now == to) {
      failed = false;
      return;
    }
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

}  // namespace tifa_libs
