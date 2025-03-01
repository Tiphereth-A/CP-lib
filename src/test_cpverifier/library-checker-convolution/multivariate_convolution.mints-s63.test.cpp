#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution"

#include "../../code/conv/conv_mval_dft.hpp"
#include "../../code/conv/ntt.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;

using ntt_t = tifa_libs::math::NTT<mint>;
using vec_t = vec<mint>;

int main() {
  u32 k, n = 1;
  tifa_libs::fin >> k;
  vecu base(k);
  for (auto &i : base) tifa_libs::fin >> i, n *= i;
  vec_t a(n), b(n);
  tifa_libs::fin >> a >> b;
  ntt_t ntt;
  tifa_libs::fout << tifa_libs::math::conv_mval_dft(ntt, a, b, base) << '\n';
  return 0;
}
