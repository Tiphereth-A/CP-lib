#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A/"

#include "../../include/graph/hlpp.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::hlpp maxflow(n, 0, n - 1);
  for (u32 i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w, maxflow.add(u, v, w);
  std::cout << maxflow.get() << '\n';
  return 0;
}