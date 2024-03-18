#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly_ln.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  poly p(n);
  std::cin >> p;
  std::cout << tifa_libs::math::poly_ln(p);
  return 0;
}
