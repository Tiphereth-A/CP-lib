#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../../src/fps/mpe/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  poly a(n), p(m);
  tifa_libs::fin_uint >> a >> p;
  tifa_libs::fout << tifa_libs::math::mpe_fps(a, p) << '\n';
  return 0;
}
