#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_12_C"

#include "../../code/graph/dijkstra.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::graph::alistw<u64> g(n);
  for (u32 i = 0, u, k; i < n; ++i) {
    std::cin >> u >> k;
    for (u32 j = 0, v, c; j < k; ++j) {
      std::cin >> v >> c;
      g.add_arc(u, v, c);
    }
  }
  auto dis = tifa_libs::graph::dijkstra(g, 0, [](u32, u32) {});
  for (u32 i = 0; i < n; ++i) std::cout << i << ' ' << dis[i] << '\n';
  return 0;
}
