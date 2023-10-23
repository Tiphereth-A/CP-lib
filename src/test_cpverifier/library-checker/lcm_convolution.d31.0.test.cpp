#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include "../../code/conv/conv_lcm.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(n + 1), b(n + 1);
  for (size_t i = 1; i <= n; ++i) std::cin >> a[i];
  for (size_t i = 1; i <= n; ++i) std::cin >> b[i];
  auto c = tifa_libs::math::conv_lcm(a, b);
  for (size_t i = 1; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
