#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../code/ds/fenwick.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::fenwick<tifa_libs::i64> fw1(n + 1);
  tifa_libs::i64 x;
  for(size_t i = 1; i <= n; ++ i) std::cin >> x, fw1.update(i, x);
  for(size_t i = 1; i <= q; ++ i) {
    size_t l, r;
    std::cin >> l >> r;
    std::cout << fw1.sum(r) - fw1.sum(l) <<'\n';
  }
  return 0;
}
