#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/adjugate_matrix"

#include "../../include/lalg/adj_mat.hpp"
#include "../../include/lalg/ge_mat.hpp"
#include "../../include/lalg/mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_ms64.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_mat(m, is_0, f); };
  std::cout << tifa_libs::math::adj_mat(a, is_0, ge);
  return 0;
}
