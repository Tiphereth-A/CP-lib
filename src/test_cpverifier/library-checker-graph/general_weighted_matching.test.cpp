#define PROBLEM "https://judge.yosupo.jp/problem/general_weighted_matching/"

#include "../../code/graph/blossomw.hpp"
// https://judge.yosupo.jp/submission/201948

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::blossomw<i64> bl(n);
  for (u32 i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    bl.add_edge(u + 1, v + 1, w);
  }
  auto res = bl();
  i64 sumw = 0;
  for (auto [_, __, w] : res) sumw += w;
  std::cout << res.size() << ' ' << sumw << '\n';
  for (auto [u, v, _] : res) std::cout << u - 1 << ' ' << v - 1 << '\n';
  return 0;
}