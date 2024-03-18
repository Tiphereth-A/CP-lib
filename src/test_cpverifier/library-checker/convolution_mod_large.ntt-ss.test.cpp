#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_large"

#include "../../code/conv/conv_ntt_large.hpp"
#include "../../code/conv/ntt.hpp"
#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_ss.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::math::NTT<mint> ntt;
  tifa_libs::fout << tifa_libs::math::conv_ntt_large(ntt, a, b) << '\n';
  return 0;
}
