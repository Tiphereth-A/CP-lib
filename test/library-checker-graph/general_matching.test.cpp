#define PROBLEM "https://judge.yosupo.jp/problem/general_matching/"

#include "../../include/graph/blossom.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::blossom bl(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    bl.add_edge(u + 1, v + 1);
  }
  auto res = bl();
  std::cout << res.size() << '\n';
  for (auto [u, v] : res) std::cout << u - 1 << ' ' << v - 1 << '\n';
  return 0;
}