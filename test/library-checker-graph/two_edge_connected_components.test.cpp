#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "../../include/graph/e_bcc.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::eog g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_edge(u, v);
  }
  graph::e_bcc bcc(g);
  std::cout << bcc.belongs.size() << '\n';
  for (auto&& b : bcc.belongs) {
    for (std::cout << b.size(); auto x : b)
      std::cout << ' ' << x;
    std::cout << '\n';
  }
  return 0;
}
