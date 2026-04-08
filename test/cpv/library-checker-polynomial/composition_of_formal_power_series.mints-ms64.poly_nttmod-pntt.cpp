#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series"

#include "../../../src/fps/comp/lib.hpp"
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
  poly f(n), g(n);
  tifa_libs::fin_uint >> f >> g;
  tifa_libs::fout << tifa_libs::comp_fps(f, g);
  return 0;
}
