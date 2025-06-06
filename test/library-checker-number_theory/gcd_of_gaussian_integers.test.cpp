#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"

#include "../../include/math/gint.hpp"

using namespace tifa_libs;
using gint = math::gint<i64, -1>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    gint x, y;
    std::cin >> x >> y;
    std::cout << gcd(x, y) << '\n';
  }
  return 0;
}
