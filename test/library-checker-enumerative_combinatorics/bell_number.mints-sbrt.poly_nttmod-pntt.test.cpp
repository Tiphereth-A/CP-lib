#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"

#include "../../include/comb/gen_bell.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_sbrt.hpp"
#include "../../include/poly/polyntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_sbrt, MOD>;
using namespace tifa_libs;
using poly = math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  auto ans = tifa_libs::math::gen_bell<poly>(n);
  flt_ (u32, i, 0, n + 1) tifa_libs::fout << ans[i] << " \n"[i == n];
  return 0;
}
