#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../code/poly/poly_ctsh.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, c;
  std::cin >> n >> m >> c;
  poly a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::poly_ctsh<poly, mint>(a, c, m) << '\n';
  return 0;
}
