#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include "../../code/math/ikth_root.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 x, k;
    std::cin >> x >> k;
    std::cout << tifa_libs::math::ikth_root(x, k) << '\n';
  }
  return 0;
}
