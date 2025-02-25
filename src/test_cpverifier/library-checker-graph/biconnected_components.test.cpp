#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include "../../code/graph/v_bcc.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_edge(u, v);
  }
  tifa_libs::graph::v_bcc bcc(g);
  std::cout << bcc.belongs.size() << '\n';
  for (u32 i = 0; i < bcc.belongs.size(); ++i) {
    std::cout << bcc.belongs[i].size() << ' ';
    for (auto x : bcc.belongs[i])
      std::cout << x << ' ';
    std::cout << '\n';
  }
  return 0;
}
