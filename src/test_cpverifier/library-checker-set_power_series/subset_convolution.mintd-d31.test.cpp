#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include "../../code/conv/conv_subset.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) tifa_libs::fin >> i;
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::math::conv_subset<mint, 20> cvs;
  tifa_libs::fout << cvs.conv(a, b) << '\n';
  return 0;
}
