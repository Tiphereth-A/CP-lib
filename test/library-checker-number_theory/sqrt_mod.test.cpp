#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "../../include/nt/qresidue.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 y, p;
    std::cin >> y >> p;
    auto res = math::qresidue(y, p);
    std::cout << (res ? (i64)res.value() : -1) << '\n';
  }
  return 0;
}
