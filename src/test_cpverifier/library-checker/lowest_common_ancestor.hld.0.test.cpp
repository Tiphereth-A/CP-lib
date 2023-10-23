#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../code/tree/lca_hld.hpp"
#include "../../code/tree/tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::graph::tree t(n);
  for (u32 i = 1, x; i < n; ++i) std::cin >> x, t.add_edge(x, i);
  tifa_libs::graph::lca_hld lca(t);
  for (u32 i = 0, u, v; i < q; ++i) {
    std::cin >> u >> v;
    std::cout << lca(u, v) << '\n';
  }
  return 0;
}
