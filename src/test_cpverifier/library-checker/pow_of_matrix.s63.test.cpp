#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include "../../code/lalg/mat.hpp"
#include "../../code/lalg/mat_pow.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s63.hpp"

using mintdata = tifa_libs::math::mintdata_s63<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
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
