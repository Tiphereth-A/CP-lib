#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../code/comb/gen_partition.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::gen_partition<poly>(n);
  return 0;
}
