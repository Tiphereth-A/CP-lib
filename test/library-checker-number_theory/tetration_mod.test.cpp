#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"

#include "../../include/math/qtetra_mod.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 a, b, m;
    std::cin >> a >> b >> m;
    std::cout << math::qtetra_mod(a, b, m) << '\n';
  }
  return 0;
}
