#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include "../../code/comb/gen_stirling2_row.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  tifa_libs::fout << tifa_libs::math::gen_stirling2_row<poly>(n);
  return 0;
}
