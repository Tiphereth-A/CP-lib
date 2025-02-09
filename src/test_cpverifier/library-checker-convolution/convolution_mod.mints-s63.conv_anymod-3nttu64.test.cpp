#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using mint_3nttu640 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 167772161>;
using mint_3nttu641 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 469762049>;
using mint_3nttu642 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 754974721>;
using ntt_3nttu640_t = tifa_libs::math::NTT<mint_3nttu640>;
using ntt_3nttu641_t = tifa_libs::math::NTT<mint_3nttu641>;
using ntt_3nttu642_t = tifa_libs::math::NTT<mint_3nttu642>;
using vec_t = vecuu;
auto conv_func(vec_t CR a, vec_t CR b) {
  ntt_3nttu640_t ntt0;
  ntt_3nttu641_t ntt1;
  ntt_3nttu642_t ntt2;
  return tifa_libs::math::conv_3ntt_u64(ntt0, ntt1, ntt2, a, b, MOD);
}

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
