#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_divmod.hpp"
#include "../../code/poly/polydata_s.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  poly_t f(n), g(m);
  std::cin >> f >> g;
  auto [q, r] = tifa_libs::math::poly_divmod(f, g);
  if (q.size() == 1 && q[0].val() == 0) q.resize(0);
  if (r.size() == 1 && r[0].val() == 0) r.resize(0);
  std::cout << q.size() << ' ' << r.size() << '\n';
  std::cout << q << '\n';
  std::cout << r << '\n';
  return 0;
}
