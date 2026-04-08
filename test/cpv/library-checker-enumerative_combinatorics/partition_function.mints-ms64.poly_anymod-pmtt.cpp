#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../../src/comb/seq/partition/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using namespace tifa_libs;
using poly = polymtt<mint>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  tifa_libs::fout << tifa_libs::gen_partition<poly>(n);
  return 0;
}
