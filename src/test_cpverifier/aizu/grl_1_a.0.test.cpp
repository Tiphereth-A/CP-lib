#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A"

#include "../../code/graph/dijkstra.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  tifa_libs::graph::adjlist<void, u32> g(n);
  for (u32 i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  constexpr u32 INF = std::numeric_limits<u32>::max() / 2 - 1;
  auto d = tifa_libs::graph::dijkstra(
      g, r, [](u32, u32) {}, INF);
  for (u32 i : d)
    if (i == INF) std::cout << "INF\n";
    else std::cout << i << '\n';
  return 0;
}
