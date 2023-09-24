#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "../../code/math/mat.hpp"
#include "../../code/math/mat_ge_basic.hpp"
#include "../../code/math/mat_inv.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  tifa_libs::u64 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };
  auto res = tifa_libs::math::inverse(a, ge);
  if (res)
    std::cout << res.value();
  else
    std::cout << "-1\n";
  return 0;
}
