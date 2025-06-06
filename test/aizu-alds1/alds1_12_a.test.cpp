#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_12_A"

#include "../../include/graph/kruskal.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  int x;
  vec<edge_tu> edges;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n) {
      std::cin >> x;
      if (i == j || !~x) continue;
      edges.emplace_back(x, i, j);
    }
  std::ranges::sort(edges);
  auto res = graph::kruskal(edges, n);
  u64 w = 0;
  flt_ (u32, i, 0, n)
    for (auto [to, v] : res.g[i]) w += v;
  std::cout << w / 2 << '\n';
  return 0;
}
