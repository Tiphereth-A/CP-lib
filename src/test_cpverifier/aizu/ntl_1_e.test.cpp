#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E"

#include "../../code/math/exgcd.hpp"

int main() {
  tifa_libs::i64 a, b;
  std::cin >> a >> b;
  auto [g, x, y] = tifa_libs::math::exgcd(a, b);
  std::cout << x << ' ' << y << '\n';
  return 0;
}
