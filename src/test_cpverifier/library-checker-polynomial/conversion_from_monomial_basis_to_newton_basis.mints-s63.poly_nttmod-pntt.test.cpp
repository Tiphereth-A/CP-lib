#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/conversion_from_monomial_basis_to_newton_basis"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/poly/cbm2n_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly f(n);
  vec<mint> p(n);
  tifa_libs::fin >> f >> p;
  tifa_libs::fout << tifa_libs::math::cbm2n_fps(f, p) << '\n';
  return 0;
}
