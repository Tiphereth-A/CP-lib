#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E"

#include "../../include/nt/exgcd.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 a, b;
  std::cin >> a >> b;
  auto [g, x, y] = math::exgcd(a, b);
  std::cout << x << ' ' << y << '\n';
  return 0;
}
