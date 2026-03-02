#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../../src/fps/ctsh/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, m, c;
  tifa_libs::fin_uint >> n >> m >> c;
  poly a(n);
  tifa_libs::fin_uint >> a;
  tifa_libs::fout << tifa_libs::math::ctsh_fps(a, mint(c), m) << '\n';
  return 0;
}
