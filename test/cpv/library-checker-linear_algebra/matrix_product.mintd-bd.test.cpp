#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../../src/lalg/ds/mat/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bd/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bd, __LINE__>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, k;
  std::cin >> n >> m >> k;
  mat a(n, m), b(m, k);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
  return 0;
}
