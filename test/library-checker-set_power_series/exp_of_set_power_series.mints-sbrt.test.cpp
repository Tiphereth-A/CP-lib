#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/poly/exp_fpssps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_sbrt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_sbrt, MOD>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  vec<mint> b(1 << n);
  tifa_libs::fin >> b;
  tifa_libs::fout << tifa_libs::math::exp_fpssps(n, b) << '\n';
  return 0;
}
