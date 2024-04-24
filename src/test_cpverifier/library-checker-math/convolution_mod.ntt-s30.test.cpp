#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/conv/conv_dft.hpp"
#include "../../code/conv/ntt.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using ntt_t = tifa_libs::math::NTT<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  ntt_t ntt;
  tifa_libs::fout << tifa_libs::math::conv_dft(ntt, a, b) << '\n';
  return 0;
}
