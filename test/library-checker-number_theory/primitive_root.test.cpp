#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include "../../include/nt/proot.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 p;
    std::cin >> p;
    std::cout << math::proot(p) << '\n';
  }
  return 0;
}
