#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../code/ds/segtree_old.hpp"
#include "../../code/math/mint_s30.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  vec<tifa_libs::math::mint_s30<998244353>> a(n);
  for (auto &x : a) std::cin >> x;
  auto min = [](tifa_libs::math::mint_s30<998244353> a, tifa_libs::math::mint_s30<998244353> b) { return std::min(a, b); };
  tifa_libs::ds::segtree_old<tifa_libs::math::mint_s30<998244353>, decltype(min)> segt(a);
  for (usz i = 1; i <= q; ++i) {
    usz opt, l, r;
    std::cin >> opt >> l >> r;
    --r;
    if (opt == 0) {
      tifa_libs::math::mint_s30<998244353> x, y;
      std::cin >> x >> y;
      segt.mul(1, 0, n - 1, l, r, x);
      segt.add(1, 0, n - 1, l, r, y);
    } else {
      std::cout << segt.querys(1, 0, n - 1, l, r) << '\n';
    }
  }
  return 0;
}
