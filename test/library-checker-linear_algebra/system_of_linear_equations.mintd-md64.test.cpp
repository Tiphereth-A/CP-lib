#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "../../include/lalg/ge_mat.hpp"
#include "../../include/lalg/leqs_solver.hpp"
#include "../../include/lalg/trans_mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_md64.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md64, __LINE__>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  mat a(n, m), b(n, 1);
  std::cin >> a >> b;

  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_mat(m, is_0, f); };

  auto res_ = tifa_libs::math::leqs_solver(a, b, is_0, ge);
  if (!res_)
    std::cout << "-1\n";
  else {
    mat &res = res_.value();
    std::cout << res.col() - 1 << '\n';
    std::cout << tifa_libs::math::transpose(res) << '\n';
  }
  return 0;
}
