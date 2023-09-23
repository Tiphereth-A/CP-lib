#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../code/math/matrix.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;

int main() {
  tifa_libs::u64 n, m, k;
  std::cin >> n >> m >> k;
  tifa_libs::math::matrix<mint> a(n, m, [](mint const &x) { return x == 0; }), b(m, k, [](mint const &x) { return x == 0; });
  std::cin >> a >> b;
  std::cout << a * b;
  return 0;
}
