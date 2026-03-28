#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_fixed_k"

#include "../../../src/comb/seq/stirling2_col/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/md64/lib.hpp"

using namespace tifa_libs;
using mint = mint_md64<__LINE__>;
using namespace tifa_libs;
using poly = polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, k;
  tifa_libs::fin_uint >> n >> k;
  auto ans = tifa_libs::gen_stirling2_col<poly>(n, k);
  flt_ (u32, i, k, n + 1) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
