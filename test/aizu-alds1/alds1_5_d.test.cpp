#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_5_D"

#include "../../include/io/ios_container.hpp"
#include "../../include/math/inversion.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n);
  std::cin >> a;
  std::cout << math::inversion(a) << '\n';
  return 0;
}
