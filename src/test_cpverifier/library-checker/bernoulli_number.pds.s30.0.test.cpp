#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../code/comb/bernoulli_gen.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polydata_s.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using polyd = tifa_libs::math::polydata_s<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::bernoulli_gen<polyd>(n);
  return 0;
}
