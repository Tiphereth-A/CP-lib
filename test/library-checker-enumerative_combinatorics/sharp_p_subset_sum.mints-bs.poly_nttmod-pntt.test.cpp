#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/math/ssts_pim_cnt.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_bs.hpp"
#include "../../include/poly/polyntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;
using namespace tifa_libs;
using poly = math::polyntt<mint>;

int main() {
  u32 n, t;
  tifa_libs::fin_uint >> n >> t;
  vecu s(n);
  tifa_libs::fin_uint >> s;
  auto v = tifa_libs::math::ssts_pim_cnt<poly>(s, t);
  flt_ (u32, i, 1, t + 1) tifa_libs::fout << v[i] << " \n"[i == t];
  return 0;
}
