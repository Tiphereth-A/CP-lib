#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_B"

#include "../../code/nt/gcd.hpp"
#include "../../code/nt/rgcd.hpp"

CEXP u32 LIMIT = 1e7;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  tifa_libs::math::RGCD rgcd(LIMIT);
  u32 x, y;
  std::cin >> x >> y;
  if (tifa_libs::max(x, y) < LIMIT) std::cout << rgcd(x, y) << '\n';
  else std::cout << tifa_libs::math::gcd(x, y) << '\n';
  return 0;
}
