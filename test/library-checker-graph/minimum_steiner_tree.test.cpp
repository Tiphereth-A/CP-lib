#define PROBLEM "https://judge.yosupo.jp/problem/minimum_steiner_tree/"

#include "../../include/graph/alist.hpp"
#include "../../include/graph/steiner_tree.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  graph::alistw<u64> e(n);
  std::map<pttu, pttu> id;
  for (u32 i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w, e.add_arc(u, v, w), e.add_arc(v, u, w);
    if (auto p = std::minmax(u, v); id[p].first == 0 || id[p].first > w) id[p] = {w, i};
  }
  u32 k;
  std::cin >> k;
  vecu a(k);
  for (auto& x : a) std::cin >> x;
  auto [sum, edges] = graph::steiner_tree<true>(e, a);
  std::cout << sum << ' ' << edges.size() << '\n';
  flt_ (u32, i, 0, (u32)edges.size()) std::cout << id[edges[i]].second << " \n"[i == edges.size() - 1];
  return 0;
}