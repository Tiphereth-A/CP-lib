#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../code/math/mint_ss.hpp"
#include "../../code/matrix/mat.hpp"
#include "../../code/matrix/mat_hafnian.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  std::cout << tifa_libs::math::hafnian(a);
  return 0;
}
