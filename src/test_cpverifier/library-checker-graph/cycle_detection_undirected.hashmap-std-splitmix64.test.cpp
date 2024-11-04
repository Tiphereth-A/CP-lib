#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

#include "../../code/graph/alist.hpp"
#include "../../code/graph/find_cycle.hpp"
//
#include "../../code/edh/hash_splitmix64.hpp"

template <class K, class V>
using hashmap = std::unordered_map<K, V, tifa_libs::hash_splitmix64>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  hashmap<pttu, u32> edges;
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    if (u == v) {
      std::cout << "1\n"
                << u << '\n'
                << i << '\n';
      return 0;
    }
    if (edges[{u, v}]) {
      std::cout << "2\n"
                << u << ' ' << v << '\n'
                << i << ' ' << edges[{u, v}] - 1 << '\n';
      return 0;
    }
    edges[{u, v}] = edges[{v, u}] = i + 1;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  auto res = tifa_libs::graph::find_cycle<false>(g);
  if (res.empty()) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << res.size() << '\n';
  flt_ (u32, i, 0, (u32)res.size()) std::cout << res[i].first << " \n"[i + 1 == res.size()];
  flt_ (u32, i, 0, (u32)res.size()) std::cout << edges[res[i]] - 1 << " \n"[i + 1 == res.size()];
  return 0;
}
