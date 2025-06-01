#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/inv_fps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d63.hpp"
#include "../../include/poly/polymtt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d63, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin >> n;
  poly p(n);
  tifa_libs::fin >> p;
  tifa_libs::fout << tifa_libs::math::inv_fps(p);
  return 0;
}
