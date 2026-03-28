#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "../../../src/fps/czt/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = mint_ms64<167772161>;
using mint_p3ntt2 = mint_ms64<469762049>;
using mint_p3ntt3 = mint_ms64<754974721>;
using poly = poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  u32 n, m;
  mint a, r;
  tifa_libs::fin_uint >> n >> m >> a >> r;
  poly f(n);
  tifa_libs::fin_uint >> f;
  tifa_libs::fout << tifa_libs::czt_fps(f, r, m, a) << '\n';
  return 0;
}
