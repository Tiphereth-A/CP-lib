#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include "../../code/lalg/mat.hpp"
#include "../../code/lalg/mat_pow.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"

using mdata = tifa_libs::math::mdata_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n, k;
  std::cin >> n >> k;
  mat a(n, n);
  std::cin >> a;
  std::cout << tifa_libs::math::pow(a, k);
  return 0;
}
