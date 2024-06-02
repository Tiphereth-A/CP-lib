#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../code/lalg/hafnian_mat.hpp"
#include "../../code/lalg/mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  std::cout << tifa_libs::math::hafnian(a);
  return 0;
}
