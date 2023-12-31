#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polysps_exp.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> b(1 << n);
  std::cin >> b;
  std::cout << tifa_libs::math::polysps_exp(n, b) << '\n';
  return 0;
}
