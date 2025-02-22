#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/poly/compinv_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly f(n);
  tifa_libs::fin >> f;
  tifa_libs::fout << tifa_libs::math::compinv_fps(f);
  return 0;
}
