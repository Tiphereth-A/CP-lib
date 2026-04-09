#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pfaffian_of_matrix
#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/lalg/mat/pfaffian/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using mat = tifa_libs::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n * 2, n * 2);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  std::cout << tifa_libs::pfaffian(a, is_0);
  return 0;
}
