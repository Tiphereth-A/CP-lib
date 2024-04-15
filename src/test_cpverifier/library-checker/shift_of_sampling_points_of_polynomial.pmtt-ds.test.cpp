#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/ctsh_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ds.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, m, c;
  tifa_libs::fin >> n >> m >> c;
  poly a(n);
  tifa_libs::fin >> a.data();
  tifa_libs::fout << tifa_libs::math::ctsh_fps(a, mint(c), m).data() << '\n';
  return 0;
}
