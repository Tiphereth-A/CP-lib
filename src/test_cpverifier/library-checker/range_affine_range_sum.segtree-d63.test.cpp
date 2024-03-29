#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../code/ds/segtree.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using T = std::pair<mint, usz>;   // sum len
using F = std::pair<mint, mint>;  // mul add

auto op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
auto e() { return T{0, 0}; }
auto mapping(F f, T a) { return T{f.first * a.first + f.second * a.second, a.second}; }
auto composition(F f, F g) {
  return F{f.first * g.first, f.first * g.second + f.second};
  /*
  g(x) = g.mul * x + g.add
  f(g(x)) = f.mul * (g.mul * x + g.add) + f.add = f.mul * g.mul * x + f.mul * g.add + f.add
  */
}
auto id() { return F(1, 0); }

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto &x : a) std::cin >> x.first, x.second = 1;
  tifa_libs::ds::segtree<T, op, e, F, mapping, composition, id> segt(a);
  for (usz i = 1; i <= q; ++i) {
    usz opt, l, r;
    std::cin >> opt >> l >> r;
    --r;
    if (opt == 0) {
      mint x, y;
      std::cin >> x >> y;
      segt.update(l, r, F{x, y});
    } else
      std::cout << segt.query(l, r).first << '\n';
  }
  return 0;
}
