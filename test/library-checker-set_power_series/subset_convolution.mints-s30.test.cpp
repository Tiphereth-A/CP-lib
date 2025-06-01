#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include "../../include/conv/conv_subset.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, MOD>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) tifa_libs::fin >> i;
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::math::conv_subset<mint, 20> cvs;
  tifa_libs::fout << cvs.conv(a, b) << '\n';
  return 0;
}
