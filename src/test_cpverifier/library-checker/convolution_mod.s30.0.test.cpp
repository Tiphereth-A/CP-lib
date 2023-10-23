#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/conv/conv_ntt.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, m;
  std::cin >> n >> m;
  tifa_libs::vec<mint> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::conv_ntt(a, b) << '\n';
  std::cout << tifa_libs::math::conv_ntt(a, b) << '\n';
  return 0;
}
