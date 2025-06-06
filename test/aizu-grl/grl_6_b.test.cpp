#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_B/"

#include "../../include/graph/ssp.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, f;
  std::cin >> n >> m >> f;
  graph::ssp mcmf(n, 0, n - 1);
  i32 c;
  for (u32 i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w >> c, mcmf.add(u, v, w, c);
  auto [flow, cost] = mcmf.get(f);
  std::cout << (flow != f ? -1 : cost) << '\n';
  return 0;
}