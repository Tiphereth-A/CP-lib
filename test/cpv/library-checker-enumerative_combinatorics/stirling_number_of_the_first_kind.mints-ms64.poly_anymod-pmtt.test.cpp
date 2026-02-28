#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include "../../../src/comb/seq/stirling1_row/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  tifa_libs::fout << tifa_libs::math::gen_stirling1_row<poly>(n);
  return 0;
}
