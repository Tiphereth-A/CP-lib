#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../code/math/fact_mint.hpp"

constexpr u64 MOD = 1000000007;

#define GENTCs_pmttd0
#define GENTCs_p3nttd0

int main() {
#define GENTCs_pmttd1
#define GENTCs_p3nttd1
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::fact_mint<poly>(n) << '\n';
  return 0;
}
