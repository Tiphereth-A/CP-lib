#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

#include "../../include/lalg/ge_mat.hpp"
#include "../../include/lalg/mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using mat = tifa_libs::math::matrix<mint>;

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
  std::cout << abs(tifa_libs::math::ge_mat(a, is_0, false));
  return 0;
}
