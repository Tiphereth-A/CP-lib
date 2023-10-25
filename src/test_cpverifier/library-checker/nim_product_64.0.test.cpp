#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"

#include "../../code/math/nim_prod.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  for (u64 i = 0, a, b; i < t; ++i) {
    std::cin >> a >> b;
    std::cout << tifa_libs::math::nimprod64(a, b) << '\n';
  }
  return 0;
}
