#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_B"

#include "../../include/opt/knapsack_01.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, w;
  std::cin >> n >> w;
  vecpt<u32> a(n);
  for (auto& [v, w] : a) std::cin >> v >> w;
  std::cout << tifa_libs::opt::knapsack_01(a, w) << '\n';
  return 0;
}
