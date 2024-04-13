#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_B"

#include "../../code/graph/cle.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  vec<std::tuple<u64, u32, u32>> arcs(m);
  for (auto& [w, u, v] : arcs) std::cin >> u >> v >> w;
  auto res = tifa_libs::graph::cle(n, r, arcs);
  u64 ans = 0;
  for (auto [w, u, v] : res) ans += w;
  std::cout << ans << '\n';
  return 0;
}
