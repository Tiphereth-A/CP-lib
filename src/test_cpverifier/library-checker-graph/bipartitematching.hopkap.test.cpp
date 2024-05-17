#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../../code/graph/hopkap.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 l, r, m;
  std::cin >> l >> r >> m;
  vecpt<u32> edges(m);
  for (auto& [u, v] : edges) std::cin >> u >> v;
  auto ans = tifa_libs::graph::hopkap(l, r, edges);
  std::cout << ans.size() << '\n';
  for (auto [u, v] : ans) std::cout << u << ' ' << v << '\n';
  return 0;
}
