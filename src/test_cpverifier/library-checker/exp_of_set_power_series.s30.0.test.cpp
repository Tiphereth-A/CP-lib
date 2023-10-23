#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polysps_exp.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> b(1 << n);
  for (auto &i : b) std::cin >> i;
  auto c = tifa_libs::math::polysps_exp(n, b);
  for (usz i = 0; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
