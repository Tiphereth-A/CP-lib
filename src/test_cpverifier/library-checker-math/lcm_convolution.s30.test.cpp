#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include "../../code/conv/conv_lcm.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(n + 1), b(n + 1);
  for (u32 i = 1; i <= n; ++i) std::cin >> a[i];
  for (u32 i = 1; i <= n; ++i) std::cin >> b[i];
  auto c = tifa_libs::math::conv_lcm(a, b);
  for (u32 i = 1; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
