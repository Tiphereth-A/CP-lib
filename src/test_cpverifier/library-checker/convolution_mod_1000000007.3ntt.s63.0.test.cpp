#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/util/ios_container.hpp"

using mint0 = tifa_libs::math::mint_s63<167772161>;
using mint1 = tifa_libs::math::mint_s63<469762049>;
using mint2 = tifa_libs::math::mint_s63<754974721>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u64> a(n), b(m);
  std::cin >> a >> b;
  std::cout << tifa_libs::math::conv_3ntt<mint0, mint1, mint2>(a, b, 1000000007) << '\n';
  return 0;
}
