#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/modinv_fps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_md64.hpp"
#include "../../include/poly/polymtt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md64, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  poly a(n), b(m);
  tifa_libs::fin_uint >> a >> b;
  auto _ = tifa_libs::math::modinv_fps(a, b);
  if (!_) tifa_libs::fout << "-1\n";
  else if (_->is_zero()) tifa_libs::fout << "0\n";
  else tifa_libs::fout << _->size() << '\n'
                       << _.value() << '\n';
  return 0;
}
