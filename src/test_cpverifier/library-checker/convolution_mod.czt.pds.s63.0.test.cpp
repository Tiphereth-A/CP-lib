#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/conv/conv_czt.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polydata_s.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using polyd = tifa_libs::math::polydata_s<mint>;
using poly = tifa_libs::math::poly<polyd>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  poly a(n), b(m);
  std::cin >> a >> b;
  std::cout << tifa_libs::math::conv_czt(a, b) << '\n';
  return 0;
}
