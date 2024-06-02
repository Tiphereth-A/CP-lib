#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

#include "../../code/lalg/ge_basic_mat.hpp"
#include "../../code/lalg/mat.hpp"
#include "../../code/lalg/rk_mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
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
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };
  std::cout << tifa_libs::math::do_rank(a, ge);
  return 0;
}
