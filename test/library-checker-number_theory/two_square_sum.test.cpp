#define PROBLEM "https://judge.yosupo.jp/problem/two_square_sum"

#include "../../include/nt/norm_fact.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 t;
  std::cin >> t;
  while (t--) {
    u64 n;
    std::cin >> n;
    auto res = math::norm_fact(n);
    std::cout << res.size() << '\n';
    for (auto [x, y] : res) std::cout << x << ' ' << y << '\n';
  }
  return 0;
}
