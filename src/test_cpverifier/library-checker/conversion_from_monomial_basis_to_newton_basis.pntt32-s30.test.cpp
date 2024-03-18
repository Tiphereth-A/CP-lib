#define PROBLEM "https://judge.yosupo.jp/problem/conversion_from_monomial_basis_to_newton_basis"

#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly_cbm2n.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly f(n);
  vec<mint> p(n);
  tifa_libs::fin >> f.data() >> p;
  tifa_libs::fout << tifa_libs::math::poly_cbm2n(f, p).data() << '\n';
  return 0;
}
