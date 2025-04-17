#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../include/util/alias_num.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 q;
  std::cin >> q;
  __gnu_pbds::tree<u64, u64,
                   std::less<u64>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>  // for benchmark with retree
      tr;
  for (u64 i = 0, op, k, v; i < q; ++i) {
    std::cin >> op >> k;
    auto it = tr.lower_bound(k);
    if (op) {
      std::cout << (it != tr.end() && it->first == k ? it->second : 0) << '\n';
    } else {
      std::cin >> v;
      if (it != tr.end() && it->first == k) it->second = v;
      else tr.insert({k, v});
    }
  }
  return 0;
}
