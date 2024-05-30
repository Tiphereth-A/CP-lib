#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../code/graph/kosaraju.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  tifa_libs::graph::kosaraju scc(g);
  std::cout << scc.dag.g.size() << '\n';
  flt_ (u32, i, 0, (u32)scc.dag.g.size()) std::cout << scc.belongs[i].size() << ' ' << scc.belongs[i] << '\n';
  return 0;
}
