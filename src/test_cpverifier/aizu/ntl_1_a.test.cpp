#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "../../code/math/pfactors.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  auto ans = tifa_libs::math::pfactors(n);
  std::cout << n << ":";
  for (auto [k, v] : ans)
    for (tifa_libs::u32 i = 0; i < v; ++i) std::cout << ' ' << k;
  std::cout << '\n';
  return 0;
}
