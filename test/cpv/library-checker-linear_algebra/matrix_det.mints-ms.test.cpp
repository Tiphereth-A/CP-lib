#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/lalg/mat/det/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, MOD>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat& m, bool f) { return tifa_libs::math::ge_mat(m, is_0, f); };
  std::cout << det(a, ge);
  return 0;
}
