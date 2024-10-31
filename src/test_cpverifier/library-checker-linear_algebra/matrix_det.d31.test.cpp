#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../code/lalg/det_mat.hpp"
#include "../../code/lalg/ge_mat.hpp"
#include "../../code/lalg/mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
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
