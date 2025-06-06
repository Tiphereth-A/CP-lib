#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include "../../include/math/ikth_root.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 x, k;
    std::cin >> x >> k;
    std::cout << math::ikth_root(x, k) << '\n';
  }
  return 0;
}
