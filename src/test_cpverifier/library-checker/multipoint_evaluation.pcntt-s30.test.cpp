#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly_mpe.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  poly a(n), p(m);
  std::cin >> a >> p;
  std::cout << tifa_libs::math::poly_mpe(a, p) << '\n';
  return 0;
}
