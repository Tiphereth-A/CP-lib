#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_12_B"

#include "../../code/graph/dijkstra.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
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
  auto dis = tifa_libs::graph::dijkstra(g, 0, fn_0);
  flt_ (u32, i, 0, n) std::cout << i << ' ' << dis[i] << '\n';
  return 0;
}
