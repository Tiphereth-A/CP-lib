#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"

#include "../../include/math/nim_prod.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  for (u64 i = 0, a, b; i < t; ++i) {
    std::cin >> a >> b;
    std::cout << math::nimprod64(a, b) << '\n';
  }
  return 0;
}
