#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include "../../../src/comb/seq/stirling2_row/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;
using namespace tifa_libs;
using poly = polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin_uint >> n;
  tifa_libs::fout << tifa_libs::gen_stirling2_row<poly>(n);
  return 0;
}
