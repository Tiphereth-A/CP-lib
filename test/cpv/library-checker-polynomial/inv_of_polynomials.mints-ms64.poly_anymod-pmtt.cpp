#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_polynomials
#include "../../../src/fps/modinv/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using namespace tifa_libs;
using poly = polymtt<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  poly a(n), b(m);
  tifa_libs::fin_uint >> a >> b;
  auto _ = tifa_libs::modinv_fps(a, b);
  if (!_) tifa_libs::fout << "-1\n";
  else if (_->is_zero()) tifa_libs::fout << "0\n";
  else tifa_libs::fout << _->size() << '\n'
                       << _.value() << '\n';
  return 0;
}
