// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_4_B"

#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/topo_sort/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  auto res = topo_sort(g);
  for (u32 i : res) std::cout << i << '\n';
  return 0;
}
