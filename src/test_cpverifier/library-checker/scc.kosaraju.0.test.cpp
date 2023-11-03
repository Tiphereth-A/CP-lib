#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../code/graph/kosaraju.hpp"

#include "../../code/graph/adjlist_rev.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::adjlist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  auto rev_g = tifa_libs::graph::adjlist_rev(g);
  tifa_libs::graph::kosaraju scc(g, rev_g);
  std::cout << scc.dag.v_size() << '\n';
  for (u32 i = 0; i < scc.dag.v_size(); ++i) std::cout << scc.belongs[i].size() << ' ' << scc.belongs[i] << '\n';
  return 0;
}
