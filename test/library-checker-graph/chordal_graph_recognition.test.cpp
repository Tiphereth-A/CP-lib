#define PROBLEM "https://judge.yosupo.jp/problem/chordal_graph_recognition/"

#include "../../include/graph/alist.hpp"
#include "../../include/graph/chordal.hpp"
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
    g.add_arc(v, u);
  }
  for (auto& i : g.g) std::ranges::sort(i);
  graph::chordal chd(g);
  if (auto res = chd.template is_chordal_graph<true>(); res) std::cout << "NO\n"
                                                                       << res->size() << '\n'
                                                                       << res.value() << '\n';
  else std::cout << "YES\n"
                 << chd.peo << '\n';
  return 0;
}