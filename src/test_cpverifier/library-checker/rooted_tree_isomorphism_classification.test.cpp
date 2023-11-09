#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include "../../code/tree/tree_hash_rooted.hpp"
#include "../../code/util/hash_splitmix64.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  tifa_libs::hash_splitmix64::set_seed();
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::graph::tree tr(n);
  for (u32 i = 1, p; i < n; ++i) {
    std::cin >> p;
    tr.add_arc(i, p), tr.add_arc(p, i);
  }
  auto ans = tifa_libs::graph::tree_hash_rooted(tr, tifa_libs::hash_splitmix64());
  std::map<u64, vec<u32>> dict;
  for (u32 i = 0; i < n; ++i) dict[ans[i]].push_back(i);
  std::cout << dict.size() << '\n';
  u32 cnt = 0;
  for (auto&& [k, v] : dict) {
    for (auto i : v) ans[i] = cnt;
    ++cnt;
  }
  std::cout << ans << '\n';
  return 0;
}
