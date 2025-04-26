#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../include/lalg/det_mat.hpp"
#include "../../include/lalg/ge_mat.hpp"
#include "../../include/lalg/mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_mat(m, is_0, f); };
  std::cout << det(a, ge);
  return 0;
}
