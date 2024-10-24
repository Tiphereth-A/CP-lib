#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../code/edh/hash_splitmix64.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 q;
  std::cin >> q;
  tifa_libs::hmap<u64, u64> hm;
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
