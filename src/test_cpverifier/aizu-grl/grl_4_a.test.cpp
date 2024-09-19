#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_4_A"

#include "../../code/graph/alist.hpp"
#include "../../code/graph/topo_sort.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  std::cout << tifa_libs::graph::topo_sort(g).empty() << '\n';
  return 0;
}
