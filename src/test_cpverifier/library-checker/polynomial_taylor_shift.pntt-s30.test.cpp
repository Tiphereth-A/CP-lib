#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly_tsh.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  mint c;
  std::cin >> n >> c;
  poly a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::poly_tsh<poly>(a, c) << '\n';
  return 0;
}
