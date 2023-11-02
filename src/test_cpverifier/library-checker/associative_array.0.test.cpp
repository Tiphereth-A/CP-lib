#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../code/util/hash_splitmix64.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
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
