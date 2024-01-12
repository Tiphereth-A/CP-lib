#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/util/ios_container.hpp"

using mdata0 = tifa_libs::math::mdata_ss<167772161>;
using mdata1 = tifa_libs::math::mdata_ss<469762049>;
using mdata2 = tifa_libs::math::mdata_ss<754974721>;
using mint0 = tifa_libs::math::mint<mdata0>;
using mint1 = tifa_libs::math::mint<mdata1>;
using mint2 = tifa_libs::math::mint<mdata2>;

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
