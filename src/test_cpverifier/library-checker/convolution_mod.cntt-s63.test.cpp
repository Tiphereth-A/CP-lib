#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/conv/conv_cntt.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<mint> a(n), b(m);
  std::cin >> a >> b;
  tifa_libs::math::CNTT<mint> cntt;
  std::cout << tifa_libs::math::conv_cntt(cntt, a, b) << '\n';
  return 0;
}
