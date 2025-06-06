#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include "../../include/graph/alist.hpp"
#include "../../include/graph/find_cycle.hpp"
//
#include "../../include/edh/hash_splitmix64.hpp"

using namespace tifa_libs;
template <class>
using hashfunc_t = hash_splitmix64;
using namespace tifa_libs;
template <class K, class V>
using hashmap = __gnu_pbds::gp_hash_table<K, V, std::conditional_t<std::is_void_v<hashfunc_t<K>>, typename __gnu_pbds::detail::default_hash_fn<K>::type, hashfunc_t<K>>>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  hashmap<pttu, u32> edges;
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    edges[{u, v}] = i;
    g.add_arc(u, v);
  }
  auto res = tifa_libs::graph::find_cycle<true>(g);
  if (res.empty()) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << res.size() << '\n';
  for (auto &&i : res) std::cout << edges[i] << '\n';
  return 0;
}
