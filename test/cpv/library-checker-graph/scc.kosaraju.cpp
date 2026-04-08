// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../../src/graph/scc/kosaraju/lib.hpp"
#include "../../../src/io/container/lib.hpp"

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
  kosaraju scc(g);
  std::cout << scc.dag.vsize() << '\n';
  flt_ (u32, i, 0, scc.dag.vsize()) std::cout << scc.belongs[i].size() << ' ' << scc.belongs[i] << '\n';
  return 0;
}
