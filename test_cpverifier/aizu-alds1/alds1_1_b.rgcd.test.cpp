#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_B"

#include "../../include/nt/gcd.hpp"
#include "../../include/nt/rgcd.hpp"

CEXP u32 LIMIT = 1e7;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  tifa_libs::math::rgcd rgcd_(LIMIT);
  u32 x, y;
  std::cin >> x >> y;
  if (std::max(x, y) < LIMIT) std::cout << rgcd_(x, y) << '\n';
  else std::cout << tifa_libs::math::gcd(x, y) << '\n';
  return 0;
}
