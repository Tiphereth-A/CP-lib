#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../../src/fps/tsh/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_ms, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_ms, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_ms, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  u32 n;
  mint c;
  tifa_libs::fin_uint >> n >> c;
  poly a(n);
  tifa_libs::fin_uint >> a;
  tifa_libs::fout << tifa_libs::math::tsh_fps(a, c) << '\n';
  return 0;
}
