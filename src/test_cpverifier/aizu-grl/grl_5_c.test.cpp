#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"

#include "../../code/tree/lca_hld.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::graph::tree tr(n);
  for (u32 i = 0, k; i < n; ++i) {
    std::cin >> k;
    for (u32 j = 0, x; j < k; ++j) {
      std::cin >> x;
      tr.add_arc(i, x), tr.add_arc(x, i);
    }
  }
  tifa_libs::graph::lca_hld lca(tr);
  u32 q;
  std::cin >> q;
  for (u32 i = 0, u, v; i < q; ++i) {
    std::cin >> u >> v;
    std::cout << lca(u, v) << '\n';
  }
  return 0;
}
