#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "../../code/conv/conv_xor.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/math/mint_d31.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::conv_xor(a, b) << '\n';
  return 0;
}
