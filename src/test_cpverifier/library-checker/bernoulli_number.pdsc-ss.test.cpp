#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../code/comb/gen_bernoulli.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/polydata_scntt.hpp"

using mdata = tifa_libs::math::mdata_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using polyd = tifa_libs::math::polydata_scntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::gen_bernoulli<polyd>(n);
  return 0;
}
