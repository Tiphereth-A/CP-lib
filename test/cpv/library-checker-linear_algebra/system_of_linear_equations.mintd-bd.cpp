#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "../../../src/lalg/mat/ge/lib.hpp"
#include "../../../src/lalg/mat/leqs_solver/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/bd/lib.hpp"

using namespace tifa_libs;
using mint = mint_bd<__LINE__>;
using mat = tifa_libs::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  mat a(n, m), b(n, 1);
  std::cin >> a >> b;

  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat& m, bool f) { return tifa_libs::ge_mat(m, is_0, f); };

  auto res_ = tifa_libs::leqs_solver(a, b, is_0, ge);
  if (!res_)
    std::cout << "-1\n";
  else {
    mat& res = res_.value();
    std::cout << res.col() - 1 << '\n';
    std::cout << res.trans() << '\n';
  }
  return 0;
}
