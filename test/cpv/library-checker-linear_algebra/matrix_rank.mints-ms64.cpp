#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_rank
#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using mat = tifa_libs::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  if (!n || !m) {
    std::cout << "0\n";
    return 0;
  }
  mat a(n, m);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  std::cout << abs(tifa_libs::ge_mat(a, is_0, false));
  return 0;
}
