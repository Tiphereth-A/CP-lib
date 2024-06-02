#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include "../../code/graph/v_bcc.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  struct EW {
    u32 to, inv;
  };
  vvec<EW> e(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    if (u == v) continue;
    u32 tem1 = u32(e[u].size()), tem2 = u32(e[v].size());
    e[u].push_back({v, tem2});
    e[v].push_back({u, tem1});
  }
  tifa_libs::graph::v_bcc<EW> bcc(e);
  std::cout << bcc.id << '\n';
  for (u32 i = 0; i < bcc.id; ++i) {
    std::cout << bcc.belongs[i].size() << ' ';
    for (auto x : bcc.belongs[i])
      std::cout << x << ' ';
    std::cout << '\n';
  }
  return 0;
}
