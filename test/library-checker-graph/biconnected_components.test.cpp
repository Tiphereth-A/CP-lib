#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include "../../include/graph/v_bcc.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_edge(u, v);
  }
  graph::v_bcc bcc(g);
  std::cout << bcc.belongs.size() << '\n';
  for (u32 i = 0; i < bcc.belongs.size(); ++i) {
    std::cout << bcc.belongs[i].size() << ' ';
    for (auto x : bcc.belongs[i])
      std::cout << x << ' ';
    std::cout << '\n';
  }
  return 0;
}
