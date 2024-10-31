#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/adjugate_matrix"

#include "../../code/lalg/adj_mat.hpp"
#include "../../code/lalg/ge_mat.hpp"
#include "../../code/lalg/mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
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
