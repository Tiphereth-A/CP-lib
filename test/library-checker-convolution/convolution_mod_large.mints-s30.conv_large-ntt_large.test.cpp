#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_large"

#include "../../include/conv/conv_ntt_large.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/conv/ntt.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using ntt_ntt_large_t = tifa_libs::math::NTT<mint>;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  ntt_ntt_large_t ntt;
  return tifa_libs::math::conv_ntt_large(ntt, a, b);
}

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}