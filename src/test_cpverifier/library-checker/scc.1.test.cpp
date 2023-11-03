#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../code/graph/tarjan.hpp"
#include "../../code/util/ios_container.hpp"


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::adjlist e(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    e.add_arc(u, v);
  }
  tifa_libs::graph::tarjan scc(e);
  tifa_libs::graph::adjlist g(scc.id);
  vec<u32> in(scc.id);
  std::queue<u32> q;
  for (u32 i = 0, x, y; i < n; ++i)
    for (auto v : e[i])
      if ((x = scc.scc_id[i]) != (y = scc.scc_id[v.to])) g.add_arc(x, y), ++in[y];
  for (u32 i = 0; i < scc.id; ++i)
    if (!in[i]) q.push(i);
  std::cout << scc.id << '\n';
  while (!q.empty()) {
    u32 u = q.front(); q.pop();
    std::cout << scc.belongs[u].size() << ' ' << scc.belongs[u] << '\n';
    for(auto v: g[u]) {
      -- in[v.to];
      if(!in[v.to]) q.push(v.to);
    }
  }
  return 0;
}
