#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include "../../code/math/mat_det.hpp"
#include "../../code/math/mat_ge_euclid.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, m;
  std::cin >> n >> m;
  mint::set_mod(m);
  if (!n) {
    std::cout << "1\n";
    return 0;
  }
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  auto div = [](mint const &x, mint const &y) { return x.val() / y.val(); };
  auto ge = [&is_0, &div](mat &m, bool f) { return tifa_libs::math::ge_euclid(m, is_0, div, f); };
  std::cout << det(a, ge);
  return 0;
}
