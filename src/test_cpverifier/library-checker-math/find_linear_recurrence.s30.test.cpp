#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/berlekamp_massey.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<mint> a(n);
  std::cin >> a;
  auto b = tifa_libs::math::berlekamp_massey(a);
  std::cout << b.size() - 1 << '\n';
  for (u32 i = 1; i < b.size(); ++i) std::cout << -b[i] << " \n"[i + 1 == b.size()];
  return 0;
}
