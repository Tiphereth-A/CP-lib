#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_modinv.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mdata = tifa_libs::math::mdata_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s32<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  poly_t a(n), b(m);
  std::cin >> a >> b;
  auto _ = tifa_libs::math::poly_modinv(a, b);
  if (!_.has_value()) std::cout << "-1\n";
  else if (_.value().empty()) std::cout << "0\n";
  else std::cout << _.value().size() << '\n'
                 << _.value() << '\n';

  return 0;
}
