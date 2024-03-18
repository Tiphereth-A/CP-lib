#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s30.hpp"
#include "../../code/io/ios_container.hpp"

using mintdata0 = tifa_libs::math::mintdata_s30<167772161>;
using mintdata1 = tifa_libs::math::mintdata_s30<469762049>;
using mintdata2 = tifa_libs::math::mintdata_s30<754974721>;
using mint0 = tifa_libs::math::mint<mintdata0>;
using mint1 = tifa_libs::math::mint<mintdata1>;
using mint2 = tifa_libs::math::mint<mintdata2>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u64> a(n), b(m);
  std::cin >> a >> b;
  std::tuple<tifa_libs::math::NTT32<mint0>, tifa_libs::math::NTT32<mint1>, tifa_libs::math::NTT32<mint2>> ntt3;
  std::cout << tifa_libs::math::conv_3ntt_u64(ntt3, a, b, 1000000007) << '\n';
  return 0;
}
