#ifndef TIFALIBS_GRAPH_STEINER_TREE
#define TIFALIBS_GRAPH_STEINER_TREE

#include "../ds/radix_heap.hpp"
#include "alistw.hpp"

namespace tifa_libs::graph {

template <class T, bool with_deg>
class steiner_tree {
  alistw<T, with_deg> CR e;
  vecu CR a;

 public:
  vvecu dp;

  steiner_tree(alistw<T, with_deg> CR E, vecu CR A) : e(E), a(A) { build(); }

  void build() {
    dp = vvecu(e.g.size(), vecu(1 << a.size(), INT32_MAX));
    flt_ (u32, i, 0, (u32)a.size()) dp[a[i]][1 << i] = 0;
    ds::rheapg<u32, u32> q;
    auto dij = [&](u32 s) {
      vecu vis(e.g.size(), 0);
      while (!q.empty()) {
        auto [dis, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e.g[u]) {
          if (dp[v][s] > dp[u][s] + w) {
            dp[v][s] = dp[u][s] + w;
            q.emplace(-dp[v][s], v);
          }
        }
      }
    };
    flt_ (u32, s, 1, 1_u32 << a.size()) {
      flt_ (u32, i, 0, (u32)e.g.size()) {
        for (u32 ss = s & (s - 1); ss; ss = s & (ss - 1))
          dp[i][s] = min(dp[i][s], dp[i][ss] + dp[i][s ^ ss]);
        if (dp[i][s] != INT32_MAX) q.emplace(-dp[i][s], i);
      }
      dij(s);
    }
  }
  CEXP u32 val() { return dp[a[0]][(1 << a.size()) - 1]; }
};

}  // namespace tifa_libs::graph

#endif