#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_C"

#include "../../code/graph/floyd.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  constexpr i64 INF = std::numeric_limits<i64>::max() / 2 - 1;
  tifa_libs::graph::adjmat<i64> g(n, INF);
  for (u32 i = 0; i < m; ++i) {
    u32 u, v;
    i32 w;
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  auto d = tifa_libs::graph::floyd(g, INF);
  if (!d.has_value()) {
    std::cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  for (auto const& i : d.value().data())
    for (u32 j = 0; j < n; ++j) {
      if (i[j] == INF) std::cout << "INF"
                                 << " \n"[j + 1 == n];
      else std::cout << i[j] << " \n"[j + 1 == n];
    }
  return 0;
}
