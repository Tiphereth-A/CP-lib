#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/conv/conv_dft.hpp"
#include "../../code/conv/ntt.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/util/ios_container.hpp"

using mint = tifa_libs::math::mdata_ss<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<mint> a(n), b(m);
  std::cin >> a >> b;
  tifa_libs::math::NTT<mint> ntt;
  std::cout << tifa_libs::math::conv_dft(ntt, a, b) << '\n';
  return 0;
}
