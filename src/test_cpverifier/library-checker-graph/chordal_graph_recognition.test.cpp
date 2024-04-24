#define PROBLEM "https://judge.yosupo.jp/problem/chordal_graph_recognition/"

#include "../../code/graph/chordal.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist<> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  for (auto& i : g.g) std::ranges::sort(i);
  tifa_libs::graph::chordal<> chd(g);
  if (auto res = chd.template is_chordal_graph<true>(); res.has_value()) std::cout << "NO\n"
                                                                                   << res.value().size() << '\n'
                                                                                   << res.value() << '\n';
  else std::cout << "YES\n"
                 << chd.peo << '\n';
  return 0;
}