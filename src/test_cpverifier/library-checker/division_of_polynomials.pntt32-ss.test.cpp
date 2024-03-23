#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "../../code/poly/poly_divmod.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  poly f(n), g(m);
  std::cin >> f >> g;
  auto [q, r] = tifa_libs::math::poly_divmod(f, g);
  if (q.size() == 1 && q[0].val() == 0) q.resize(0);
  if (r.size() == 1 && r[0].val() == 0) r.resize(0);
  std::cout << q.size() << ' ' << r.size() << '\n';
  std::cout << q << '\n';
  std::cout << r << '\n';
  return 0;
}
