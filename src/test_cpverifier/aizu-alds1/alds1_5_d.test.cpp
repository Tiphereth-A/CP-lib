#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_5_D"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/inversion.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::inversion(a) << '\n';
  return 0;
}
