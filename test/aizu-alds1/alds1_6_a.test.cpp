#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_6_A"

#include "../../include/fast/rsort32.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n);
  std::cin >> a;
  rsort32(a);
  std::cout << a << '\n';
  return 0;
}
