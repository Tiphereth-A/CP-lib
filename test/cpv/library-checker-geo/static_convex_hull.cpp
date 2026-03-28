#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using cvh_t = cvh<i64>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n;
    std::cin >> n;
    cvh_t poly(n);
    std::cin >> poly;
    poly.init();
    std::cout << poly.size() << '\n';
    for (auto CR i : poly.vs) std::cout << i << '\n';
  }
  return 0;
}
