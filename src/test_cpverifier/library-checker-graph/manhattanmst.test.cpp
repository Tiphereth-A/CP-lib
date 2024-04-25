#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst/"

#include "../../code/graph/kruskal.hpp"
#include "../../code/graph/manhattan_mst.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vecpt<i64> vp(n);
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