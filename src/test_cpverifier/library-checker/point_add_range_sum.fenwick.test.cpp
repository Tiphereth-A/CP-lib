#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../code/ds/fenwick.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::fenwick<u64> f(n + 1);
  u64 x;
  for (usz i = 1; i <= n; ++i) {
    std::cin >> x;
    f.add(i, x);
  }
  for (usz i = 1; i <= q; ++i) {
    usz op, l, r;
    std::cin >> op >> l >> r;
    if (!op) f.add(l + 1, r);
    else std::cout << f.sum(r) - f.sum(l) << '\n';
  }
  return 0;
}
