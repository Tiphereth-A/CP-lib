#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../../src/comb/seq/partition/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/md/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;
using namespace tifa_libs;
using mint_p3ntt1 = mint_ms64<167772161>;
using mint_p3ntt2 = mint_ms64<469762049>;
using mint_p3ntt3 = mint_ms64<754974721>;
using poly = poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin_uint >> n;
  tifa_libs::fout << tifa_libs::gen_partition<poly>(n);
  return 0;
}
