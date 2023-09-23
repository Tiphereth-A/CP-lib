#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "../../code/math/matrix.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;

int main() {
  tifa_libs::u64 n;
  std::cin >> n;
  tifa_libs::math::matrix<mint> a(n, n, [](mint const &x) { return x == 0; });
  std::cin >> a;
  auto res = a.inverse();
  if (res)
    std::cout << res.value();
  else
    std::cout << "-1\n";
  return 0;
}
