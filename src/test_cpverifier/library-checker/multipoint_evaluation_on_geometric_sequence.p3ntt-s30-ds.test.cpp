#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "../../code/poly/poly_czt.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ds.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using mint1 = tifa_libs::math::mint_s30<167772161>;
using mint2 = tifa_libs::math::mint_s30<469762049>;
using mint3 = tifa_libs::math::mint_s30<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  mint a, r;
  std::cin >> n >> m >> a >> r;
  poly f(n);
  std::cin >> f;
  std::cout << tifa_libs::math::poly_czt(f, r, m, a) << '\n';
  return 0;
}
