#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include "../../../src/conv/lcm/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vec<mint> a(n + 1), b(n + 1);
  flt_ (u32, i, 1, n + 1) std::cin >> a[i];
  flt_ (u32, i, 1, n + 1) std::cin >> b[i];
  auto c = tifa_libs::conv_lcm(a, b);
  flt_ (u32, i, 1, (u32)c.size()) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
