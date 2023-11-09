#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_12_A"

#include "../../code/graph/kruskal.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  int x;
  vec<pt3<u32>> edges;
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j < n; ++j) {
      std::cin >> x;
      if (i == j || !~x) continue;
      edges.emplace_back(x, i, j);
    }
  std::sort(edges.begin(), edges.end());
  auto res = tifa_libs::graph::kruskal(edges, n);
  u64 w = 0;
  for (u32 i = 0; i < n; ++i)
    for (auto [to, v] : res.g[i]) w += v;
  std::cout << w / 2 << '\n';
  return 0;
}
