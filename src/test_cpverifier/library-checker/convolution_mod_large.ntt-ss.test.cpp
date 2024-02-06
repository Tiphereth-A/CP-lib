#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_large"

#include "../../code/conv/conv_ntt_large.hpp"
#include "../../code/conv/ntt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_ss.hpp"
#include "../../code/util/ios_container.hpp"

using mintdata = tifa_libs::math::mintdata_ss<998244353>;
using mint = tifa_libs::math::mint<mintdata>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<mint> a(n), b(m);
  std::cin >> a >> b;
  tifa_libs::math::NTT<mint> ntt;
  std::cout << tifa_libs::math::conv_ntt_large(ntt, a, b) << '\n';
  return 0;
}
