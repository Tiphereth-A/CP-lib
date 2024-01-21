#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_B"

#include "../../code/nt/rgcd.hpp"

constexpr u32 LIMIT = 1e7;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::math::RGCD rgcd(LIMIT);
  u32 x, y;
  std::cin >> x >> y;
  if (std::max(x, y) < LIMIT) std::cout << rgcd(x, y) << '\n';
  else std::cout << std::gcd(x, y) << '\n';
  return 0;
}
