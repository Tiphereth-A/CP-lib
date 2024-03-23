#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../code/io/ios_container.hpp"
#include "../../code/poly/polysps_exp.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;

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
