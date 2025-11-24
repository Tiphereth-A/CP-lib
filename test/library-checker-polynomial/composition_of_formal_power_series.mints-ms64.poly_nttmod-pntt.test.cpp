#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/comp_fps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_ms64.hpp"
#include "../../include/poly/polyntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;
using namespace tifa_libs;
using poly = math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin_uint >> n;
  poly f(n), g(n);
  tifa_libs::fin_uint >> f >> g;
  tifa_libs::fout << tifa_libs::math::comp_fps(f, g);
  return 0;
}
