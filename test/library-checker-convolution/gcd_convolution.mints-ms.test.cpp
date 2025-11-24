#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include "../../include/conv/conv_gcd.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_ms.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vec<mint> a(n + 1), b(n + 1);
  flt_ (u32, i, 1, n + 1) std::cin >> a[i];
  flt_ (u32, i, 1, n + 1) std::cin >> b[i];
  auto c = tifa_libs::math::conv_gcd(a, b);
  flt_ (u32, i, 1, (u32)c.size()) std::cout << c[i] << " \n"[i + 1 == c.size()];
  return 0;
}
