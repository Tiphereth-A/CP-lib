#define AUTO_GENERATED
#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../../src/math/fact/mod/lib.hpp"

using namespace tifa_libs;
CEXP u64 MOD = 1000000007;

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
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::fact_mint<poly>(n) << '\n';
  return 0;
}
