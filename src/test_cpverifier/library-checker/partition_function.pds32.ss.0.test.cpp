#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../code/comb/partition_gen.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using polyd = tifa_libs::math::polydata_s32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::partition_gen<polyd>(n);
  return 0;
}
