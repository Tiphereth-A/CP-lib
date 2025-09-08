#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/sqrt_fps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/poly/polyntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;
using namespace tifa_libs;
using poly = math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly p(n);
  tifa_libs::fin >> p;
  auto res = tifa_libs::math::sqrt_fps(p);
  if (!res) tifa_libs::fout << "-1\n";
  else tifa_libs::fout << res.value() << '\n';
  return 0;
}
