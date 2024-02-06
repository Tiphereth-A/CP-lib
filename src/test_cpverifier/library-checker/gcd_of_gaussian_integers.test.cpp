#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"

#include "../../code/math/gauss_int.hpp"

using gint = tifa_libs::math::gint<i64, -1>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    gint x, y;
    std::cin >> x >> y;
    std::cout << gcd(x, y) << '\n';
  }
  return 0;
}
