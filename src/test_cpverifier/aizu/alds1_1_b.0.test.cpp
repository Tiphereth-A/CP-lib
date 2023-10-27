#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_B"

#include "../../code/math/gcd128.hpp"
#include "../../code/util/ios128.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i128 x, y;
  std::cin >> x >> y;
  std::cout << tifa_libs::math::gcd_128(x, y) << '\n';
  return 0;
}
