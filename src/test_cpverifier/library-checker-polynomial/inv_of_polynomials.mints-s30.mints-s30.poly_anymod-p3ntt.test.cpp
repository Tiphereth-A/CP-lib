#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/modinv_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using mint_p3ntt1 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 167772161>;
using mint_p3ntt2 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 469762049>;
using mint_p3ntt3 = tifa_libs::math::mint<tifa_libs::math::mint_s30, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly a(n), b(m);
  tifa_libs::fin >> a >> b;
  auto _ = tifa_libs::math::modinv_fps(a, b);
  if (!_.has_value()) tifa_libs::fout << "-1\n";
  else if (_.value().is_zero()) tifa_libs::fout << "0\n";
  else tifa_libs::fout << _.value().size() << '\n'
                       << _.value() << '\n';
  return 0;
}
