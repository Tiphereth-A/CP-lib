#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/conversion_from_monomial_basis_to_newton_basis"

#include "../../../src/fps/cbm2n/lib.hpp"
#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using namespace tifa_libs;
using poly = polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  poly f(n);
  vec<mint> p(n);
  tifa_libs::fin_uint >> f >> p;
  tifa_libs::fout << tifa_libs::cbm2n_fps(f, p) << '\n';
  return 0;
}
