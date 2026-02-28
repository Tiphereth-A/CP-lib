#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include "../../../src/lalg/ds/matsp/lib.hpp"
#include "../../../src/lalg/mat/det_rd/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md64, __LINE__>;
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
