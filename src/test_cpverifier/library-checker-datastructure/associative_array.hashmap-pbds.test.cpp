#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../code/util/util.hpp"
//
template <class K, class V>
using hashmap = hmap<K, V>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 q;
  std::cin >> q;
  hashmap<u64, u64> hm;
  for (u64 i = 0, op, k, v; i < q; ++i) {
    std::cin >> op >> k;
    if (op) std::cout << hm[k] << '\n';
    else {
      std::cin >> v;
      hm[k] = v;
    }
  }
  return 0;
}
