#define PROBLEM "https://yukicoder.me/problems/no/3024"

#include "../../code/edh/discretization.hpp"
#include "../../code/enum/enum_subset.hpp"
#include "../../code/io/ios_container.hpp"
#include "../../code/math/rational.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n);
  std::cin >> a;
  vvec<tifa_libs::math::rational<i64>> dp(1 << n);
  flt_(u32, i, 0, n) dp[1 << i].emplace_back((i64)a[i]);
  for (u32 i = 0, ed_ = 1 << n; i < ed_; ++i) {
    if (std::popcount(i) <= 1) continue;
    tifa_libs::enum_subset<>::set(i);
    for (auto j : tifa_libs::enum_subset<>{})
      for (auto x : dp[i - j])
        for (auto y : dp[j]) {
          if (x == y) {
            std::cout << "YES\n";
            return 0;
          }
          if (i != (1_u32 << n) - 1_u32) dp[i].push_back(x + y), dp[i].push_back(x - y), dp[i].push_back(x * y), dp[i].push_back(x / y);
        }
    dp[i] = tifa_libs::uniq(dp[i]);
  }
  std::cout << "NO\n";
  return 0;
}
