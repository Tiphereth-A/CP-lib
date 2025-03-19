#ifndef TIFALIBS_GRAPH_STEINER_TREE
#define TIFALIBS_GRAPH_STEINER_TREE

#include "../ds/radix_heap.hpp"
#include "../util/traits_graph.hpp"

namespace tifa_libs::graph {

template <alistw_c G>
class steiner_tree {
  G CR e;
  vecu CR a;

 public:
  vvecu dp;
  steiner_tree(G CR e, vecu CR a) NE : e(e), a(a), dp(e.size(), vecu(1 << a.size(), INT32_MAX)) { build(); }
  CEXP u32 val() NE { return dp[a[0]][(1 << a.size()) - 1]; }

 private:
  void build() NE {
    flt_ (u32, i, 0, (u32)a.size()) dp[a[i]][1 << i] = 0;
    ds::rheapg<u32, u32> q;
    auto dij = [&](u32 s) NE {
      vecu vis(e.size(), 0);
      while (!q.empty()) {
        auto [dis, u] = q.top();
        if (q.pop(); vis[u]) continue;
        for (vis[u] = 1; auto [v, w] : e[u])
          if (dp[v][s] > dp[u][s] + w) dp[v][s] = dp[u][s] + w, q.emplace(-dp[v][s], v);
      }
    };
    flt_ (u32, s, 1, 1_u32 << a.size()) {
      flt_ (u32, i, 0, (u32)e.size()) {
        for (u32 ss = s & (s - 1); ss; ss = s & (ss - 1)) dp[i][s] = min(dp[i][s], dp[i][ss] + dp[i][s ^ ss]);
        if (dp[i][s] != INT32_MAX) q.emplace(-dp[i][s], i);
      }
      dij(s);
    }
  }
};

}  // namespace tifa_libs::graph

#endif