#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../code/comb/gen_partition.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::gen_partition<poly>(n);
  return 0;
}
