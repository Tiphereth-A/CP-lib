#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../../src/ds/bst/rbt/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 q;
  std::cin >> q;
  rbtree<pttuu> tr;
  for (u64 i = 0, op, k, v; i < q; ++i) {
    std::cin >> op >> k;
    auto it = tr.lower_bound({k, 0});
    if (op) {
      std::cout << (it && it->data.first == k ? it->data.second : 0) << '\n';
    } else {
      std::cin >> v;
      if (it && it->data.first == k) it->data.second = v;
      else tr.insert({k, v});
    }
  }
  return 0;
}
