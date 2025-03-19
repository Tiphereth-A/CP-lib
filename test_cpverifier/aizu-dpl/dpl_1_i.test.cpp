#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_I"

#include "../../include/opt/knapsack_mixed_huge.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n, w;
  std::cin >> n >> w;
  vec<pt3uu> a(n);
  for (auto& [v, w, num] : a) std::cin >> v >> w >> num;
  std::cout << tifa_libs::opt::knapsack_mixed_huge(a, w) << '\n';
  return 0;
}
