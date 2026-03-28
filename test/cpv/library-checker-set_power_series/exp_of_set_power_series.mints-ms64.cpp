#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/sps/exp/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  vec<mint> b(1 << n);
  tifa_libs::fin_uint >> b;
  tifa_libs::fout << tifa_libs::exp_fpssps(n, b) << '\n';
  return 0;
}
