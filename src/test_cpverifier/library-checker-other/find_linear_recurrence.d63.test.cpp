#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/berlekamp_massey.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint_d63<-1>;

int main() {
  mint::set_mod(MOD);
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
