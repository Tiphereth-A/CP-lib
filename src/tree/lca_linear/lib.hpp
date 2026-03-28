#pragma once

#include "../../bit/lowbit/lib.hpp"
#include "../../graph/ds/graph_c/lib.hpp"

namespace tifa_libs {

template <graph_c G>
class lca_linear {
  vecu d, in, asc, head;

 public:
  CEXPE lca_linear(G CR g) NE : d(g.vsize()), in(g.vsize()), asc(g.vsize()), head(g.vsize() + 1) {
    vecptu ord;
    auto dfs = [&](auto&& f, u32 u, u32 p) -> void {
      ord.emplace_back(u, p);
      for (in[u] = (u32)ord.size(); u32 v : g[u])
        if (v != p)
          if (d[v] = 1 + d[u], f(f, v, u), head[in[v]] = u; lowbit(in[u]) < lowbit(in[v])) in[u] = in[v];
    };
    dfs(dfs, 0, 0);
    for (auto [u, p] : ord) asc[u] = asc[p] | lowbit(in[u]);
  }

  CEXP u32 operator()(u32 u, u32 v) CNE {
    if (u32 j = in[u] ^ in[v]) {
      j = asc[u] & asc[v] & -std::bit_floor(j);
      if (auto k = std::bit_floor(asc[u] ^ j)) u = head[(in[u] & -k) | k];
      if (auto k = std::bit_floor(asc[v] ^ j)) v = head[(in[v] & -k) | k];
    }
    retif_((d[u] < d[v]), u, v);
  }
};

}  // namespace tifa_libs
