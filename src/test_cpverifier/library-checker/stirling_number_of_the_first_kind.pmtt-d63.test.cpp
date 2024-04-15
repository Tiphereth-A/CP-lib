#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include "../../code/comb/gen_stirling1_row.hpp"
#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n;
  tifa_libs::fin >> n;
  tifa_libs::fout << tifa_libs::math::gen_stirling1_row<poly>(n).data();
  return 0;
}
