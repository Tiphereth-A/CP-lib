#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential_non_commutative_group"

#include "../../include/ds/dsu_weighted.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/lalg/mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_dbrt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_dbrt, __LINE__>;
using mat = tifa_libs::math::matrix<mint>;

auto inv(mat CR m) {  // ensure det(m)==1
  return mat({{m(1, 1), -m(0, 1)}, {-m(1, 0), m(0, 0)}});
}
auto op(mat CR x, mat CR y) { return x * y; }

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_weighted<mat, op, inv> dsu(n, mat({{1, 0}, {0, 1}}));
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) {
      if (!dsu.same(u, v)) std::cout << "-1\n";
      else std::cout << dsu.diff(u, v).data() << '\n';
    } else {
      mat k(2, 2);
      std::cin >> k;
      std::cout << dsu.merge(u, v, k) << '\n';
    }
  }
  return 0;
}
