#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../../src/fps/pow/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = mint_bs<MOD>;
using namespace tifa_libs;
using poly = polyntt<mint>;

int main() {
  u32 n;
  u64 m;
  tifa_libs::fin_uint >> n >> m;
  poly a(n);
  tifa_libs::fin_uint >> a;
  tifa_libs::fout << tifa_libs::pow_fps(a, m) << '\n';
  return 0;
}
