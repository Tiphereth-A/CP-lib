#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include "../../code/conv/conv_lcm.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<mint> a(n), b(n);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  auto c = tifa_libs::math::conv_lcm(a, b);
  for (size_t i = 0; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
