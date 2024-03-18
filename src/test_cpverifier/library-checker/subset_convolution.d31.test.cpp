#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include "../../code/conv/conv_subset.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d31.hpp"
#include "../../code/io/ios_container.hpp"

using mintdata = tifa_libs::math::mintdata_d31<-1>;
using mint = tifa_libs::math::mint<mintdata>;

int main() {
  mintdata::set_mod(998244353);
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
