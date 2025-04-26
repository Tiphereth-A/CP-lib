#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "../../include/io/ios_container.hpp"
#include "../../include/math/berlekamp_massey.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vec<mint> a(n);
  std::cin >> a;
  auto b = tifa_libs::math::berlekamp_massey(a);
  std::cout << b.size() - 1 << '\n';
  flt_ (u32, i, 1, (u32)b.size()) std::cout << -b[i] << " \n"[i + 1 == b.size()];
  return 0;
}
