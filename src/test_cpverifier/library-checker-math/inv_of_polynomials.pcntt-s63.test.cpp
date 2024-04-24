#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/modinv_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
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
