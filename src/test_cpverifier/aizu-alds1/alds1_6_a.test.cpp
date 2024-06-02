#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_6_A"

#include "../../code/fast/rsort32.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n);
  std::cin >> a;
  tifa_libs::rsort32(a);
  std::cout << a << '\n';
  return 0;
}
