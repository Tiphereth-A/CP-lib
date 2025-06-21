#ifndef TIFALIBS_GRAPH_STEINER_TREE
#define TIFALIBS_GRAPH_STEINER_TREE

#include "../ds/radix_heap.hpp"
#include "../util/traits_graph.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::graph {

template <bool get_edges, alistw_c G, class T = TPN G::w_t>
auto steiner_tree(G CR g, spnu x, vec<T> CR vw = {}, T INF = inf_v<T>) NE {
  const u32 n = (u32)g.size(), k = (u32)x.size();
  const bool has_vweight = !vw.empty();
  if (has_vweight) assert(!uint_c<T>);
  vvec<T> dp(n, vec<T>(1 << k, INF));
  flt_ (u32, i, 0, k) dp[x[i]][1 << i] = 0;
  ds::rheap<T, u32> q;
  auto dij = [&](u32 s) {
    while (!q.empty()) {
      auto [dis, u] = q.top();
      if (q.pop(); dp[u][s] != dis) continue;
      for (auto [v, w] : g[u])
        if (dp[v][s] > dis + w)
          q.emplace(dp[v][s] = dis + w, v);
    }
  };
  std::queue<u32> qw;
  auto bm = [&](u32 s) {
    vecb inq(n);
    while (!qw.empty()) {
      u32 u = qw.front();
      qw.pop(), inq[u] = false;
      for (auto [v, w] : g[u])
        if (dp[v][s] > dp[u][s] + w + vw[v])
          if (dp[v][s] = dp[u][s] + w + vw[v]; !inq[v]) inq[v] = true, qw.push(v);
    }
  };
  if (has_vweight)
    flt_ (u32, s, 1, 1_u32 << k) {
      flt_ (u32, i, 0, n) {
        for (u32 t = s & (s - 1); t; t = s & (t - 1))
          if (dp[i][s] > dp[i][t] + dp[i][s ^ t] - vw[i]) dp[i][s] = dp[i][t] + dp[i][s ^ t] - vw[i];
        if (dp[i][s] < INF) qw.push(i);
      }
      bm(s);
    }
  else
    flt_ (u32, s, 1, 1_u32 << k) {
      flt_ (u32, i, 0, n) {
        for (u32 t = s & (s - 1); t; t = s & (t - 1))
          if (dp[i][s] > dp[i][t] + dp[i][s ^ t]) dp[i][s] = dp[i][t] + dp[i][s ^ t];
        if (dp[i][s] < INF) q.emplace(dp[i][s], i);
      }
      dij(s);
    }
  if CEXP (get_edges) {
    vecptu edges;
    if (dp[x[0]].back() == INF) return std::make_pair(INF, edges);
    u32 pos = 0;
    T dp_pos = dp[0].back();
    flt_ (u32, i, 1, n)
      if (dp[i].back() < dp_pos) dp_pos = dp[pos = i].back();
    std::queue<pttu> sp({{(1 << k) - 1, pos}});
    while (sp.size()) {
      auto [s, pos] = sp.front();
      sp.pop();
      bool f;
      do {
        for (f = false; auto [to, w] : g[pos])
          if (dp[to][s] + w == dp[pos][s]) {
            edges.push_back(std::minmax(to, pos)), f = true, pos = to;
            break;
          }
      } while (f);
      if (dp[pos][s])
        for (u32 t = (s - 1) & s; t; t = (t - 1) & s)
          if (dp[pos][t] + dp[pos][s ^ t] == dp[pos][s]) {
            sp.emplace(t, pos), sp.emplace(s ^ t, pos);
            break;
          }
    }
    return std::make_pair(dp[x[0]].back(), edges);
  } else return dp[x[0]].back();
}

}  // namespace tifa_libs::graph

#endif