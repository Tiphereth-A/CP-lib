#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "../../code/lalg/mat.hpp"
#include "../../code/lalg/mat_ge_basic.hpp"
#include "../../code/lalg/mat_inv.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s30.hpp"

using mintdata = tifa_libs::math::mintdata_s30<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };
  auto res = tifa_libs::math::mat_inv(a, is_0, ge);
  if (res)
    std::cout << res.value();
  else
    std::cout << "-1\n";
  return 0;
}
