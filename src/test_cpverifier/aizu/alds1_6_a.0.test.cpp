#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_6_A"

#include "../../code/fast/rsort32.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> a(n);
  std::cin >> a;
  tifa_libs::rsort32(a);
  std::cout << a << '\n';
  return 0;
}
