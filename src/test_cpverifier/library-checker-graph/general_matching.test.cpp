#define PROBLEM "https://judge.yosupo.jp/problem/general_matching/"

#include "../../code/graph/blossom.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::blossom bl(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    bl.add_edge(u + 1, v + 1);
  }
  auto res = bl();
  std::cout << res.size() << '\n';
  for (auto [u, v] : res) std::cout << u - 1 << ' ' << v - 1 << '\n';
  return 0;
}