#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../../src/fps/tsh/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md64, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  mint c;
  tifa_libs::fin_uint >> n >> c;
  poly a(n);
  tifa_libs::fin_uint >> a;
  tifa_libs::fout << tifa_libs::math::tsh_fps(a, c) << '\n';
  return 0;
}
