#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 1000000007;

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint_ss.hpp"

using mint0 = tifa_libs::math::mint_ss<167772161>;
using mint1 = tifa_libs::math::mint_ss<469762049>;
using mint2 = tifa_libs::math::mint_ss<754974721>;
using ntt3_t = std::tuple<tifa_libs::math::NTT32<mint0>, tifa_libs::math::NTT32<mint1>, tifa_libs::math::NTT32<mint2>>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vecu64 a(n), b(m);
  tifa_libs::fin >> a >> b;
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt_u64(ntt3, a, b, MOD) << '\n';
  return 0;
}
