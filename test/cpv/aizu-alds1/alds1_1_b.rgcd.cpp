#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_B"

#include "../../../src/nt/gl/gcd/lib.hpp"
#include "../../../src/nt/gl/rgcd/lib.hpp"

using namespace tifa_libs;
CEXP u32 LIMIT = 1e7;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  rgcd rgcd_(LIMIT);
  u32 x, y;
  std::cin >> x >> y;
  if (std::max(x, y) < LIMIT) std::cout << rgcd_(x, y) << '\n';
  else std::cout << gcd(x, y) << '\n';
  return 0;
}
