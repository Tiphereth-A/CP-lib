#ifndef TIFA_LIBS_GRAPH_STEINER_TREE
#define TIFA_LIBS_GRAPH_STEINER_TREE

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T>
class steiner_tree {
  const vvec<std::pair<u32, T>>& e;
  const vec<u32>& a;

 public:
  vec<vec<u32>> dp;
  steiner_tree(const vvec<std::pair<u32, T>>& E, const vec<u32>& A) : e(E), a(A) { build(); }
  void build() {
    dp = vec<vec<u32>>(e.size(), vec<u32>(1 << a.size(), INT32_MAX));
    for (u32 i = 0; i < a.size(); ++i) dp[a[i]][1 << i] = 0;

    std::priority_queue<std::pair<u32, u32>> q;
    auto dij = [&](u32 s) {
      vec<u32> vis(e.size(), 0);
      while (!q.empty()) {
        auto [dis, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e[u]) {
          if (dp[v][s] > dp[u][s] + w) {
            dp[v][s] = dp[u][s] + w;
            q.push({-dp[v][s], v});
          }
        }
      }
    };

    for (u32 s = 1; s < (1 << a.size()); ++s) {
      for (u32 i = 0; i < e.size(); ++i) {
        for (u32 ss = s & (s - 1); ss; ss = s & (ss - 1))
          dp[i][s] = std::min(dp[i][s], dp[i][ss] + dp[i][s ^ ss]);
        if (dp[i][s] != INT32_MAX) q.push({-dp[i][s], i});
      }
      dij(s);
    }
  }
  u32 val() { return dp[a[0]][(1 << a.size()) - 1]; }
};

}  // namespace tifa_libs::graph

#endif