#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/conv/conv_ntt32.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<mint> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::conv_ntt32(a, b) << '\n';
  return 0;
}
