#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A"

#include "../../code/graph/kruskal.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vec<edge_tu> e(m);
  for (auto& [w, u, v] : e) std::cin >> u >> v >> w;
  std::ranges::sort(e);
  auto tr = tifa_libs::graph::kruskal(e, n);
  u32 ret = 0;
  flt_ (u32, i, 0, n)
    for (auto [to, w] : tr.g[i]) ret += w;
  std::cout << ret / 2 << '\n';
  return 0;
}
