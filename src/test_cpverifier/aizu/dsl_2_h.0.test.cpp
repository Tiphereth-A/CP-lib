#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H"

#include "../../code/ds/segtree_old.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  vec<i32> a(n);
  auto min = [](i32 a, i32 b) { return std::min(a, b); };
  tifa_libs::ds::segtree_old<i32, decltype(min)> segt(a);
  for (usz i = 1; i <= q; ++i) {
    usz opt, l, r;
    std::cin >> opt >> l >> r;
    if (opt == 0) {
      i32 x;
      std::cin >> x;
      segt.add(1, 0, n - 1, l, r, x);
    } else {
      std::cout << segt.querym(1, 0, n - 1, l, r, min) << '\n';
    }
  }
  return 0;
}
