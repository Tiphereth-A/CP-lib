#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_C"

#include "../../include/graph/floyd.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  CEXP i64 INF = tifa_libs::inf_v<i64>;
  tifa_libs::graph::amat<i64> g(n, INF);
  flt_ (u32, i, 0, m) {
    u32 u, v;
    i32 w;
    std::cin >> u >> v >> w;
    g.set_arc(u, v, w);
  }
  if (!tifa_libs::graph::floyd(g, INF)) {
    std::cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  for (auto CR i : g.g)
    flt_ (u32, j, 0, n) {
      if (i[j] == INF) std::cout << "INF"
                                 << " \n"[j + 1 == n];
      else std::cout << i[j] << " \n"[j + 1 == n];
    }
  return 0;
}
