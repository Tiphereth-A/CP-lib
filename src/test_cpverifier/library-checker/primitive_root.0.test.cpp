#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include "../../code/math/proot_u64.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 p;
    std::cin >> p;
    std::cout << tifa_libs::math::proot_u64(p) << '\n';
  }
  return 0;
}
