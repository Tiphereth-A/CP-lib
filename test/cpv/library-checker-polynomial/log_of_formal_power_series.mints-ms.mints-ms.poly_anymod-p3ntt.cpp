#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include "../../../src/fps/ln/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = mint_ms<167772161>;
using mint_p3ntt2 = mint_ms<469762049>;
using mint_p3ntt3 = mint_ms<754974721>;
using poly = poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  poly p(n);
  tifa_libs::fin_uint >> p;
  tifa_libs::fout << tifa_libs::ln_fps(p);
  return 0;
}
