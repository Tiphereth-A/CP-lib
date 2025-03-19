#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_B"

#include "../../include/graph/cle.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  vec<edge_t<u64>> arcs(m);
  for (auto& [w, u, v] : arcs) std::cin >> u >> v >> w;
  auto res = tifa_libs::graph::cle(n, r, arcs);
  u64 ans = 0;
  for (auto [w, u, v] : res) ans += w;
  std::cout << ans << '\n';
  return 0;
}
