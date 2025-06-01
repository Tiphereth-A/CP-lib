#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include "../../include/edh/hash_splitmix64.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/tree/tree_hash_rooted.hpp"

using namespace tifa_libs;
int main() {
  hash_splitmix64::set_seed();
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  graph::tree tr(n);
  for (u32 i = 1, p; i < n; ++i) {
    std::cin >> p;
    tr.add_arc(i, p), tr.add_arc(p, i);
  }
  auto ans = graph::tree_hash_rooted(tr, hash_splitmix64());
  map<u64, vecu> dict;
  flt_ (u32, i, 0, n) dict[ans[i]].push_back(i);
  std::cout << dict.size() << '\n';
  u32 cnt = 0;
  for (auto&& [k, v] : dict) {
    for (auto i : v) ans[i] = cnt;
    ++cnt;
  }
  std::cout << ans << '\n';
  return 0;
}
