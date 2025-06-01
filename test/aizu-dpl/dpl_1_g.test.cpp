#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_G"

#include "../../include/opt/knapsack_mixed.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, w;
  std::cin >> n >> w;
  opt::knapsack_mixed<i32> kn(w);
  for (u32 i = 0; i < n; ++i) {
    i32 v;
    u32 w, m;
    std::cin >> v >> w >> m;
    kn.add(w, v, m);
  }
  std::cout << *std::ranges::max_element(kn.result()) << '\n';
  return 0;
}