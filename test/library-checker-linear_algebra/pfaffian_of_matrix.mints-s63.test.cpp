#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/pfaffian_of_matrix"

#include "../../include/lalg/mat.hpp"
#include "../../include/lalg/pfaffian_mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n * 2, n * 2);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  std::cout << tifa_libs::math::pfaffian(a, is_0);
  return 0;
}
