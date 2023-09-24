#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../code/math/mat.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  tifa_libs::u64 n, m, k;
  std::cin >> n >> m >> k;
  mat a(n, m), b(m, k);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
  return 0;
}
