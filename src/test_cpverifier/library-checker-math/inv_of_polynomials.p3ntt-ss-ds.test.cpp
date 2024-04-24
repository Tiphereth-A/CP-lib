#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/modinv_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ds.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using mint1 = tifa_libs::math::mint_ss<167772161>;
using mint2 = tifa_libs::math::mint_ss<469762049>;
using mint3 = tifa_libs::math::mint_ss<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly a(n), b(m);
  tifa_libs::fin >> a.data() >> b.data();
  auto _ = tifa_libs::math::modinv_fps(a, b);
  if (!_.has_value()) tifa_libs::fout << "-1\n";
  else if (_.value().empty()) tifa_libs::fout << "0\n";
  else tifa_libs::fout << _.value().size() << '\n'
                       << _.value().data() << '\n';
  return 0;
}
