#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_B"

#include "../../include/graph/alist.hpp"
#include "../../include/graph/bm.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  tifa_libs::graph::alistw<i32> g(n);
  flt_ (u32, i, 0, m) {
    u32 u, v;
    i32 w;
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  CEXP i32 INF = tifa_libs::inf_v<i32>;
  auto d = tifa_libs::graph::bellman_ford(g, r, fn_0, INF);
  if (!d.has_value()) {
    std::cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  for (i32 i : d.value())
    if (i == INF) std::cout << "INF\n";
    else std::cout << i << '\n';
  return 0;
}
