#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "../../code/conv/conv_and.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::conv_and(a, b) << '\n';
  return 0;
}
