#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../code/math/mint_ds.hpp"
#include "../../code/lalg/mat.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n, m, k;
  std::cin >> n >> m >> k;
  mat a(n, m), b(m, k);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
  return 0;
}
