#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_G"

#include "../../../src/comb/ball_box/dia/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/md64/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_md64<__LINE__>;
using namespace tifa_libs;
using mint_p3ntt1 = mint_ms64<167772161>;
using mint_p3ntt2 = mint_ms64<469762049>;
using mint_p3ntt3 = mint_ms64<754974721>;
using poly = poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  std::cout << tifa_libs::ball_box_dia<poly>(n, k) << '\n';
  return 0;
}
