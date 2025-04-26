#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst/"

#include "../../include/graph/kruskal.hpp"
#include "../../include/graph/manhattan_mst.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecptii vp(n);
  for (auto& [x, y] : vp) std::cin >> x >> y;
  auto res = tifa_libs::graph::manhattan_mst(vp);
  std::ranges::sort(res);
  auto mst = tifa_libs::graph::kruskal(res, n);
  i64 sum = 0;
  flt_ (u32, u, 0, n)
    for (auto [v, w] : mst.g[u])
      if (v > u) sum += w;
  std::cout << sum << '\n';
  flt_ (u32, u, 0, n)
    for (auto [v, w] : mst.g[u])
      if (v > u) std::cout << u << ' ' << v << '\n';
  return 0;
}