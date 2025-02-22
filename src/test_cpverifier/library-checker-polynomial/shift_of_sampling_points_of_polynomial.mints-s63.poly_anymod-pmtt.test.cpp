#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/poly/ctsh_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  u32 n, m, c;
  tifa_libs::fin >> n >> m >> c;
  poly a(n);
  tifa_libs::fin >> a;
  tifa_libs::fout << tifa_libs::math::ctsh_fps(a, mint(c), m) << '\n';
  return 0;
}
