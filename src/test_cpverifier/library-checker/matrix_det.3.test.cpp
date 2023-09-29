#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../code/math/mint_sd.hpp"
#include "../../code/matrix/mat.hpp"
#include "../../code/matrix/mat_det.hpp"
#include "../../code/matrix/mat_ge_basic.hpp"

using mint = tifa_libs::math::mint_sd<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };
  std::cout << det(a, ge);
  return 0;
}
