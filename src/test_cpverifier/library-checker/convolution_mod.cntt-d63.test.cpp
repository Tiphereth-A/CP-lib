#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/conv/conv_cntt.hpp"
#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using cntt_t = tifa_libs::math::CNTT<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  cntt_t cntt;
  tifa_libs::fout << tifa_libs::math::conv_cntt(cntt, a, b) << '\n';
  return 0;
}
