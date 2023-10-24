#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A"

#include "../../code/tree/diameter_w.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::graph::tree<u32> tr(n);
  for (u32 i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    tr.add_edge(u, v, w);
  }
  std::cout << std::get<2>(tifa_libs::graph::tree_diameter_w(tr)) << '\n';
  return 0;
}
