#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../code/graph/tarjan.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;

  vvecu e(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    e[u].push_back(v);
  }
  tifa_libs::graph::tarjan scc;
  scc.build(e);
  vvecu g(scc.id);
  vecu in(scc.id);
  for (u32 i = 0, x, y; i < n; ++i)
    for (auto v : e[i])
      if ((x = scc.scc_id[i]) != (y = scc.scc_id[v])) g[x].push_back(y), ++in[y];
  std::queue<u32> q;
  for (u32 i = 0; i < scc.id; ++i)
    if (!in[i]) q.push(i);
  std::cout << scc.id << '\n';
  while (!q.empty()) {
    u32 u = q.front();
    q.pop();
    std::cout << scc.belongs[u].size() << ' ' << scc.belongs[u] << '\n';
    for (auto v : g[u]) {
      --in[v];
      if (!in[v]) q.push(v);
    }
  }
  return 0;
}
