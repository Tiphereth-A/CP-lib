#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/conv/conv_czt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s30.hpp"
#include "../../code/poly/polydata_s.hpp"

using mintdata = tifa_libs::math::mintdata_s30<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
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
