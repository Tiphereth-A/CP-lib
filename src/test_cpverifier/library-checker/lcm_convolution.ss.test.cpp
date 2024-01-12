#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include "../../code/conv/conv_lcm.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"

using mdata = tifa_libs::math::mint_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(n + 1), b(n + 1);
  for (usz i = 1; i <= n; ++i) std::cin >> a[i];
  for (usz i = 1; i <= n; ++i) std::cin >> b[i];
  auto c = tifa_libs::math::conv_lcm(a, b);
  for (usz i = 1; i < c.size(); ++i) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
