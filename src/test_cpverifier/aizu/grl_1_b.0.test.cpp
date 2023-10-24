#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_B"

#include "../../code/graph/bm.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  tifa_libs::graph::adjlist<i32> g(n);
  for (u32 i = 0; i < m; ++i) {
    u32 u, v;
    i32 w;
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  constexpr i32 INF = std::numeric_limits<i32>::max() / 2 - 1;
  auto d = tifa_libs::graph::bellman_ford(
      g, r, [](u32, u32) {}, INF);
  if (!d.has_value()) {
    std::cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  for (i32 i : d.value())
    if (i == INF) std::cout << "INF\n";
    else std::cout << i << '\n';
  return 0;
}
