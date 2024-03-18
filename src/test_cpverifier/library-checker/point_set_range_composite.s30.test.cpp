#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../../code/ds/segtree.hpp"
#include "../../code/math/mint_s30.hpp"

using Ty = tifa_libs::math::mint_s30<998244353>;
using T = std::pair<Ty, Ty>;
using F = T;

auto op(T a, T b) {  // b(a(x))
  swap(a, b);
  return T{a.first * b.first, a.first * b.second + a.second};
}
auto e() { return T{1, 0}; }
auto id() { return e(); }
auto mapping(F f, T a) { return op(f, a); }
auto composition(F, F) { return F(1, 0); }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto& x : a) std::cin >> x.first >> x.second;
  tifa_libs::ds::segtree<T, op, e, F, mapping, composition, id> seg(a);
  for (u32 i = 0, opt; i < q; ++i) {
    std::cin >> opt;
    if (opt == 0) {
      u32 x;
      Ty y, z;
      std::cin >> x >> y >> z;
      seg.set(x, T{y, z});
    } else {
      u32 x, y;
      Ty z;
      std::cin >> x >> y >> z;
      auto ret = seg.query(x, y - 1);
      std::cout << ret.first * z + ret.second << '\n';
    }
  }
  return 0;
}
