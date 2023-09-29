#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_C"

#include "../../code/math/rgcd.hpp"

constexpr tifa_libs::u32 LIMIT = 1e7;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  tifa_libs::u32 ans;
  std::cin >> ans;
  tifa_libs::math::RGCD rgcd(LIMIT);
  for (tifa_libs::u32 i = 0, x; i < n; ++i) {
    std::cin >> x;
    if (ans < LIMIT) (ans /= rgcd(ans, x)) *= x;
    else ans = std::lcm(ans, x);
  }
  std::cout << ans << '\n';
  return 0;
}
