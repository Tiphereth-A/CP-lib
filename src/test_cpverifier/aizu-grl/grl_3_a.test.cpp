#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_A"

#include "../../code/graph/v_bcc.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_edge(u, v);
  }
  tifa_libs::graph::v_bcc<true, false, false> bcc(g);
  flt_ (u32, i, 0, n)
    if (bcc.vcut[i]) std::cout << i << '\n';
  return 0;
}
