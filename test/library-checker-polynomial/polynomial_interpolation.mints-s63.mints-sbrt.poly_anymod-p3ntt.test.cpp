#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/interp_fps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"
#include "../../include/math/mint_sbrt.hpp"
#include "../../include/poly/poly3ntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_sbrt, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_sbrt, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_sbrt, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly a(n), b(n);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << tifa_libs::math::interp_fps(a, b) << '\n';
  return 0;
}
