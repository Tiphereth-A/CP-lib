#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/ctsh_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using mint1 = tifa_libs::math::mint_ss<167772161>;
using mint2 = tifa_libs::math::mint_ss<469762049>;
using mint3 = tifa_libs::math::mint_ss<754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  u32 n, m, c;
  tifa_libs::fin >> n >> m >> c;
  poly a(n);
  tifa_libs::fin >> a;
  tifa_libs::fout << tifa_libs::math::ctsh_fps(a, mint(c), m).data() << '\n';
  return 0;
}
