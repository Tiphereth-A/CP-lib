#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include "../../code/comb/gen_stirling2_row.hpp"
#include "../../code/io/fastio.hpp"

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
  u32 n;
  tifa_libs::fin >> n;
  tifa_libs::fout << tifa_libs::math::gen_stirling2_row<poly>(n).data();
  return 0;
}
