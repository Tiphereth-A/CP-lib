#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../../src/fps/mpe/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using namespace tifa_libs;
using poly = polyntt<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  poly a(n), p(m);
  tifa_libs::fin_uint >> a >> p;
  tifa_libs::fout << tifa_libs::mpe_fps(a, p) << '\n';
  return 0;
}
