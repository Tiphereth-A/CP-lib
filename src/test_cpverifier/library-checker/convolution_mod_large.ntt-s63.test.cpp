#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_large"

#include "../../code/conv/conv_ntt_large.hpp"
#include "../../code/conv/ntt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s63.hpp"
#include "../../code/io/fastio.hpp"

using mintdata = tifa_libs::math::mintdata_s63<998244353>;
using mint = tifa_libs::math::mint<mintdata>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::math::NTT<mint> ntt;
  tifa_libs::fout << tifa_libs::math::conv_ntt_large(ntt, a, b) << '\n';
  return 0;
}
