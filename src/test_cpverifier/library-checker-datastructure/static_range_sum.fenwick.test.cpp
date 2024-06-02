#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../code/ds/fenwick.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::fenwick<u64> f(n + 1);
  u64 x;
  fle_ (u32, i, 1, n) {
    std::cin >> x;
    f.add(i, x);
  }
  fle_ (u32, i, 1, q) {
    u32 l, r;
    std::cin >> l >> r;
    std::cout << f.sum(r) - f.sum(l) << '\n';
  }
  return 0;
}
