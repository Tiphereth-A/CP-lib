#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include "../../code/nt/proot.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 p;
    std::cin >> p;
    std::cout << tifa_libs::math::proot(p) << '\n';
  }
  return 0;
}
