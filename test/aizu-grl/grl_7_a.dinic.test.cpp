#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_7_A/"

#include "../../include/graph/dinic.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 l, r, m;
  std::cin >> l >> r >> m;
  u32 s = l + r, t = l + r + 1;
  graph::dinic big(l + r + 2);
  flt_ (u32, i, 0, l) big.add(s, i, 1);
  flt_ (u32, i, 0, r) big.add(i + l, t, 1);
  for (u32 i = 0, u, v; i < m; ++i) std::cin >> u >> v, big.add(u, v + l, 1);
  std::cout << big.get(s, t) << '\n';
  return 0;
}
