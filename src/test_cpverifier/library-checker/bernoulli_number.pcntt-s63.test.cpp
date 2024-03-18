#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../code/comb/gen_bernoulli.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::gen_bernoulli<poly>(n);
  return 0;
}
