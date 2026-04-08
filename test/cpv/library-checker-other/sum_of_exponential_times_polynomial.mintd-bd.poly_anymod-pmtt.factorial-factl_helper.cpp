#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial"

#include "../../../src/comb/seq/pows/lib.hpp"
#include "../../../src/math/ipaf/sum/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/bd/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"

using namespace tifa_libs;
using mint = mint_bd<__LINE__>;
using namespace tifa_libs;
using poly = polymtt<mint>;
using namespace tifa_libs;
using fact_t = factl_helper<poly>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 r, d;
  u64 n;
  std::cin >> r >> d >> n;
  auto p = tifa_libs::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::sum_ipaf<mint, fact_t>(p, mint(r), n);
  return 0;
}
