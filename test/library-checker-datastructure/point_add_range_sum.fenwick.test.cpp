#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../include/ds/fenwick.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vecuu a(n + 1);
  flt_ (u32, i, 1, n + 1) std::cin >> a[i];
  ds::fenwick<u64> f(a);
  flt_ (u32, i, 1, q + 1) {
    u32 op, l, r;
    std::cin >> op >> l >> r;
    if (!op) f.add(l + 1, r);
    else std::cout << f.sum(r) - f.sum(l) << '\n';
  }
  return 0;
}
