#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_7_A/"

#include "../../code/graph/hopkap.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 l, r, m;
  std::cin >> l >> r >> m;
  vecptu edges(m);
  for (auto& [u, v] : edges) std::cin >> u >> v;
  auto ans = tifa_libs::graph::hopkap(l, r, edges);
  std::cout << ans.size() << '\n';
  return 0;
}
