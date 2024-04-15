#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/interp_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin >> n;
  poly a(n), b(n);
  tifa_libs::fin >> a.data() >> b.data();
  tifa_libs::fout << tifa_libs::math::interp_fps(a, b).data() << '\n';
  return 0;
}
