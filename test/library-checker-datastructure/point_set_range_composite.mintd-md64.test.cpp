#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../../include/ds/segtree.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_md64.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md64, __LINE__>;
using Ty = mint;
using T = std::pair<Ty, Ty>;
using F = T;

auto op(T a, T b) {  // b(a(x))
  std::swap(a, b);
  return T{a.first * b.first, a.first * b.second + a.second};
}
void mapping(T& a, F f) { a = op(f, a); }
void composition(F& x, F) { x = F(1, 0); }

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto& x : a) std::cin >> x.first >> x.second;
  tifa_libs::ds::segtree<T, op, F, mapping, composition> seg({1, 0}, {1, 0}, a);
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
      auto ret = seg.query(x, y);
      std::cout << ret.first * z + ret.second << '\n';
    }
  }
  return 0;
}
