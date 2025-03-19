#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

CEXP u32 MOD = 1000000007;

#include "../../include/conv/conv_3ntt.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"
#include "../../include/math/mint_s30.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using mint_3ntt0 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 167772161>;
using mint_3ntt1 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 469762049>;
using mint_3ntt2 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 754974721>;
using ntt_3ntt0_t = tifa_libs::math::NTT<mint_3ntt0>;
using ntt_3ntt1_t = tifa_libs::math::NTT<mint_3ntt1>;
using ntt_3ntt2_t = tifa_libs::math::NTT<mint_3ntt2>;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  ntt_3ntt0_t ntt0;
  ntt_3ntt1_t ntt1;
  ntt_3ntt2_t ntt2;
  return tifa_libs::math::conv_3ntt(ntt0, ntt1, ntt2, a, b);
}

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
