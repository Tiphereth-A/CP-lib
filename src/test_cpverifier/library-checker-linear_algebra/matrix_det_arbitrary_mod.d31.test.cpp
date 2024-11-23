#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include "../../code/lalg/det_mat.hpp"
#include "../../code/lalg/ge_mat.hpp"
#include "../../code/lalg/mat.hpp"
//
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;

using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, MOD;
  std::cin >> n >> MOD;
  mint::set_mod(MOD);
  if (!n) {
    std::cout << "1\n";
    return 0;
  }
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_mat<mint, decltype(is_0), true>(m, is_0, f); };
  std::cout << det(a, ge);
  return 0;
}
