#pragma once

#include "../../../util/alias/others/lib.hpp"
#include "../../ds/lib.hpp"

namespace tifa_libs {

template <tree_c G, class T>
CEXP vec<T> tree_sumvw(G CR tr, vec<T> CR v_weight) NE {
  vec<T> sumvw = v_weight;
  auto dfs = [&](auto&& dfs, u32 u, u32 fa) NE -> void {
    for (auto v : tr[u])
      if ((u32)v != fa) dfs(dfs, (u32)v, u), sumvw[u] += sumvw[v];
  };
  dfs(dfs, tr.root, -1_u32);
  return sumvw;
}

}  // namespace tifa_libs
