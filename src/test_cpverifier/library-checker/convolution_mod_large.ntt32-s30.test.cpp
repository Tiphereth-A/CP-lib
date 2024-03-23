#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_large"

#include "../../code/conv/conv_ntt_large.hpp"
#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/conv/ntt32.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using ntt_t = tifa_libs::math::NTT32<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  ntt_t ntt;
  tifa_libs::fout << tifa_libs::math::conv_ntt_large(ntt, a, b) << '\n';
  return 0;
}
