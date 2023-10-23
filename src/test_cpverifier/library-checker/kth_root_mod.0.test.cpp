#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_mod"

#include "../../code/math/kth_root.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 k, y, p;
    std::cin >> k >> y >> p;
    auto res = tifa_libs::math::kth_root(y, k, p);
    std::cout << (res ? (i64)res.value() : -1) << '\n';
  }
  return 0;
}
