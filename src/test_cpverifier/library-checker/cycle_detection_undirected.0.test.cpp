#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

#include "../../code/graph/find_cycle.hpp"
#include "../../code/util/hash_splitmix64.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  tifa_libs::hmap<ptt<u32>, u32> edges;
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    edges[{u, v}] = edges[{v, u}] = i;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  auto res = tifa_libs::graph::find_cycle<false>(g);
  if (res.empty()) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << res.size() << '\n';
  for (u32 i = 0; i < res.size(); ++i) std::cout << res[i].first << " \n"[i + 1 == res.size()];
  for (u32 i = 0; i < res.size(); ++i) std::cout << edges[res[i]] << " \n"[i + 1 == res.size()];
  return 0;
}
