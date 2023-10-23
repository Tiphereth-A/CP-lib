#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/util/ios_container.hpp"

using mint0 = tifa_libs::math::mint_ss<167772161>;
using mint1 = tifa_libs::math::mint_ss<469762049>;
using mint2 = tifa_libs::math::mint_ss<754974721>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u64> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  std::cout << tifa_libs::math::conv_3ntt<mint0, mint1, mint2>(a, b, 1000000007) << '\n';
  return 0;
}
