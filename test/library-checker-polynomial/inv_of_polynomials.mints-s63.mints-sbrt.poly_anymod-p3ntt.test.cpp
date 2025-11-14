#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/modinv_fps.hpp"

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
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly a(n), b(m);
  tifa_libs::fin >> a >> b;
  auto _ = tifa_libs::math::modinv_fps(a, b);
  if (!_) tifa_libs::fout << "-1\n";
  else if (_->is_zero()) tifa_libs::fout << "0\n";
  else tifa_libs::fout << _->size() << '\n'
                       << _.value() << '\n';
  return 0;
}
