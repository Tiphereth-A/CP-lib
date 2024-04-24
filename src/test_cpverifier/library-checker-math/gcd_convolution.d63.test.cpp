#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include "../../code/conv/conv_gcd.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint_d63<-1>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(n + 1), b(n + 1);
  for (u32 i = 1; i <= n; ++i) std::cin >> a[i];
  for (u32 i = 1; i <= n; ++i) std::cin >> b[i];
  auto c = tifa_libs::math::conv_gcd(a, b);
  for (u32 i = 1; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}