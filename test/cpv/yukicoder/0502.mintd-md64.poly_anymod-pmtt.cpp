#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/502
#include "../../../src/math/fact/mod/lib.hpp"

using namespace tifa_libs;
CEXP u64 MOD = 1000000007;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/md64/lib.hpp"

using namespace tifa_libs;
using mint = mint_md64<__LINE__>;
using namespace tifa_libs;
using poly = polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::fact_mint<poly>(n) << '\n';
  return 0;
}
