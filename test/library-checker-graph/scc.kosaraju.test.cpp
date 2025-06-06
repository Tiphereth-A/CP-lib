#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../include/graph/kosaraju.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  graph::kosaraju scc(g);
  std::cout << scc.dag.g.size() << '\n';
  flt_ (u32, i, 0, (u32)scc.dag.g.size()) std::cout << scc.belongs[i].size() << ' ' << scc.belongs[i] << '\n';
  return 0;
}
