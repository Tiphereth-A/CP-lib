#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A"

#include "../../code/graph/kruskal.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<std::tuple<u32, u32, u32>> e(m);
  for (auto& [w, u, v] : e) std::cin >> u >> v >> w;
  std::sort(e.begin(), e.end());
  auto tr = tifa_libs::graph::kruskal<u32>(e, n);
  u32 ret = 0;
  for (u32 i = 0; i < n; ++i)
    for (auto [to, w] : tr.g[i]) ret += w;
  std::cout << ret / 2 << '\n';
  return 0;
}
