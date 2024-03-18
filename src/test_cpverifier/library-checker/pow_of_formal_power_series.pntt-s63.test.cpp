#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly_pow.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  u64 m;
  tifa_libs::fin >> n >> m;
  poly a(n);
  tifa_libs::fin >> a.data();
  tifa_libs::fout << tifa_libs::math::poly_pow(a, m).data() << '\n';
  return 0;
}
