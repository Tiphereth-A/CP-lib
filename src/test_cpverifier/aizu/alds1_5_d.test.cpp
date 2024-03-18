#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_5_D"

#include "../../code/util/inversion.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<u32> a(n);
  std::cin >> a;
  std::cout << tifa_libs::inversion(a) << '\n';
  return 0;
}
