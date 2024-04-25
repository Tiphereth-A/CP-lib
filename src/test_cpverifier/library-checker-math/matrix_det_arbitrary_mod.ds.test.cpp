#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include "../../code/lalg/det_mat.hpp"
#include "../../code/lalg/ge_euclid_mat.hpp"
#include "../../code/lalg/mat.hpp"
//
#include "../../code/math/mint_ds.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
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
  auto div = [](cT_(mint) x, cT_(mint) y) -> mint { return x.val() / y.val(); };
  auto ge = [&is_0, &div](mat &m, bool f) { return tifa_libs::math::ge_euclid(m, is_0, div, f); };
  std::cout << det(a, ge);
  return 0;
}
