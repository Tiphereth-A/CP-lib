#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_C"

#include "../../code/math/is_prime.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  u32 cnt = 0;
  while (t--) {
    u32 p;
    std::cin >> p;
    cnt += tifa_libs::math::is_prime(p);
  }
  std::cout << cnt << '\n';
  return 0;
}
