#define PROBLEM "https://judge.yosupo.jp/problem/three_edge_connected_components"

#include "../../code/graph/e_tcc.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_edge(u, v);
  }
  tifa_libs::graph::e_tcc tcc(g);
  std::cout << tcc.belongs.size() << '\n';
  for (auto &&b : tcc.belongs) {
    std::cout << b.size();
    for (auto x : b)
      std::cout << ' ' << x;
    std::cout << '\n';
  }
  return 0;
}
