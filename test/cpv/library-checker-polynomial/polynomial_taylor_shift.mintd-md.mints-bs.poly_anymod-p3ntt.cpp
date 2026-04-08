#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../../src/fps/tsh/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"
#include "../../../src/math/ds/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;
using namespace tifa_libs;
using mint_p3ntt1 = mint_bs<167772161>;
using mint_p3ntt2 = mint_bs<469762049>;
using mint_p3ntt3 = mint_bs<754974721>;
using poly = poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  mint c;
  tifa_libs::fin_uint >> n >> c;
  poly a(n);
  tifa_libs::fin_uint >> a;
  tifa_libs::fout << tifa_libs::tsh_fps(a, c) << '\n';
  return 0;
}
