#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A"

#include "../../code/graph/dijkstra.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  tifa_libs::graph::alistw<u32> g(n);
  for (u32 i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  CEXP u32 INF = std::numeric_limits<u32>::max() / 2 - 1;
  auto d = tifa_libs::graph::dijkstra(g, r, fn_0, INF);
  for (u32 i : d)
    if (i == INF) std::cout << "INF\n";
    else std::cout << i << '\n';
  return 0;
}
