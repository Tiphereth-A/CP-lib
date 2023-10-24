#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include "../../code/conv/conv_subset.hpp"
#include "../../code/math/mint_ds.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mint_ds<-1>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  tifa_libs::math::conv_subset<mint, 20> cvs;
  std::cout << cvs.conv(a, b) << '\n';
  return 0;
}
