#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../code/ds/segtree_old.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint_d63<-1>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  vec<mint> a(n);
  for (auto &x : a) std::cin >> x;
  auto min = [](mint a, mint b) { return std::min(a, b); };
  tifa_libs::ds::segtree_old<mint, decltype(min)> segt(a);
  for (u32 i = 1; i <= q; ++i) {
    u32 opt, l, r;
    std::cin >> opt >> l >> r;
    --r;
    if (opt == 0) {
      mint x, y;
      std::cin >> x >> y;
      segt.mul(1, 0, n - 1, l, r, x);
      segt.add(1, 0, n - 1, l, r, y);
    } else {
      std::cout << segt.querys(1, 0, n - 1, l, r) << '\n';
    }
  }
  return 0;
}
