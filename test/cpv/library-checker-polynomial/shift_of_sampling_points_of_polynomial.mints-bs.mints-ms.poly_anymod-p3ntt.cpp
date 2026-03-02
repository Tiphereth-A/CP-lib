#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../../src/fps/ctsh/lib.hpp"
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
  u32 n, m, c;
  tifa_libs::fin_uint >> n >> m >> c;
  poly a(n);
  tifa_libs::fin_uint >> a;
  tifa_libs::fout << tifa_libs::math::ctsh_fps(a, mint(c), m) << '\n';
  return 0;
}
