#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include "../../include/ds/dsu_weighted.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d31, __LINE__>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_weighted<mint> dsu(n);
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) {
      if (!dsu.same(u, v)) std::cout << "-1\n";
      else std::cout << dsu.diff(u, v) << '\n';
    } else {
      i64 k;
      std::cin >> k;
      std::cout << dsu.merge(u, v, k) << '\n';
    }
  }
  return 0;
}
