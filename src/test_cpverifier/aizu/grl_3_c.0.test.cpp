#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_C"

#include "../../code/graph/adjlist_rev.hpp"
#include "../../code/graph/scc.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::adjlist<void> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  tifa_libs::graph::SCC scc(g, tifa_libs::graph::adjlist_rev(g));
  u32 q;
  std::cin >> q;
  for (u32 i = 0, u, v; i < q; ++i) {
    std::cin >> u >> v;
    std::cout << (scc.scc_id[u] == scc.scc_id[v]) << '\n';
  }
  return 0;
}
