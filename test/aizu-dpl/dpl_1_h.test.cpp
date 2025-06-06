#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_H"

#include "../../include/opt/knapsack_01.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n, w;
  std::cin >> n >> w;
  vecpt<u64> a(n);
  for (auto& [v, w] : a) std::cin >> v >> w;
  std::cout << opt::knapsack_01(a, w) << '\n';
  return 0;
}
