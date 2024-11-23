#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "../../code/ds/segtree.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using T = std::pair<mint, usz>;   // sum len
using F = std::pair<mint, mint>;  // mul add

auto op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
auto e() { return T{0, 0}; }
auto mapping(T a, F f) {
  return T{f.first * a.first + f.second * a.second, a.second};
}
auto composition(F f, F g) {
  return F{f.first * g.first, g.first * f.second + g.second};
  // g(x) = g.mul * x + g.add
  // f(g(x)) = f.mul * (g.mul * x + g.add) + f.add = f.mul * g.mul * x + f.mul * g.add + f.add
}
auto id() { return F{1, 0}; }

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto &x : a) std::cin >> x.first, x.second = 1;
  tifa_libs::ds::segtree<T, op, e, F, mapping, composition, id> segt(a);
  flt_ (u32, i, 1, q + 1) {
    u32 opt, l, r;
    std::cin >> opt >> l;
    if (opt == 0) {
      mint x, y;
      std::cin >> r >> x >> y;
      segt.update(l, r, F{x, y});
    } else
      std::cout << segt.query(l).first << '\n';
  }
  return 0;
}
