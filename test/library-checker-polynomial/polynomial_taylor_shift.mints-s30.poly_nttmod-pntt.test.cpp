#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/tsh_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  mint c;
  tifa_libs::fin >> n >> c;
  poly a(n);
  tifa_libs::fin >> a;
  tifa_libs::fout << tifa_libs::math::tsh_fps(a, c) << '\n';
  return 0;
}
