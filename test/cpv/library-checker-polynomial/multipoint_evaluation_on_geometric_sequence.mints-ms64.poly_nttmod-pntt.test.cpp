#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "../../../src/fps/czt/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;
using namespace tifa_libs;
using poly = math::polyntt<mint>;

int main() {
  u32 n, m;
  mint a, r;
  tifa_libs::fin_uint >> n >> m >> a >> r;
  poly f(n);
  tifa_libs::fin_uint >> f;
  tifa_libs::fout << tifa_libs::math::czt_fps(f, r, m, a) << '\n';
  return 0;
}
