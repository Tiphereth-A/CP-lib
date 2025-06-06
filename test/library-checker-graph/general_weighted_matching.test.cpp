#define PROBLEM "https://judge.yosupo.jp/problem/general_weighted_matching/"

#include "../../include/graph/blossomw.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::blossomw<i64> bl(n);
  for (u32 i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    bl.add_edge(u + 1, v + 1, w);
  }
  auto res = bl();
  i64 sumw = 0;
  for (auto [w, u, v] : res) sumw += w;
  std::cout << res.size() << ' ' << sumw << '\n';
  for (auto [w, u, v] : res) std::cout << u - 1 << ' ' << v - 1 << '\n';
  return 0;
}