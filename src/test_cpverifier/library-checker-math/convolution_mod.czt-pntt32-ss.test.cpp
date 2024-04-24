#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/conv/conv_czt.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << tifa_libs::math::conv_czt(poly(a), poly(b)) << '\n';
  return 0;
}
