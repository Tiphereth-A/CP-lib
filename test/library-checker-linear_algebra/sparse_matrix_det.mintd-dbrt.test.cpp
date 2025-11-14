#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include "../../include/lalg/det_rd_mat.hpp"
#include "../../include/lalg/matsp.hpp"
#include "../../include/rand/gen.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_dbrt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_dbrt, __LINE__>;
using mat = tifa_libs::math::matsp<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  mat a(n, n);
  for (u32 i = 0, x, y, z; i < k; ++i) {
    std::cin >> x >> y >> z;
    a(x, y) = z;
  }
  auto is0 = [](cT_(mint) x) { return x.val() == 0; };
  tifa_libs::rand::gen<u32> gen(1, mint::mod() - 1);
  std::cout << tifa_libs::math::det_rd(a, gen, is0) << '\n';
  return 0;
}
