#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../code/lalg/mat.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"

using mdata = tifa_libs::math::mdata_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n, m, k;
  std::cin >> n >> m >> k;
  mat a(n, m), b(m, k);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
  return 0;
}
