#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/adjugate_matrix"

#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/lalg/mat/adj/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;
using mat = tifa_libs::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat& m, bool f) { return tifa_libs::ge_mat(m, is_0, f); };
  std::cout << tifa_libs::adj_mat(a, is_0, ge);
  return 0;
}
