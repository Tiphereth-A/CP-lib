#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A/"

#include "../../code/graph/dinic.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::dinic maxflow(n, 0, n - 1);
  for (u32 i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w, maxflow.add(u, v, w);
  std::cout << maxflow() << '\n';
  return 0;
}