#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"

#include "../../../src/comb/seq/bell/lib.hpp"
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
  tifa_libs::fin_uint >> n;
  auto ans = tifa_libs::gen_bell<poly>(n);
  flt_ (u32, i, 0, n + 1) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
