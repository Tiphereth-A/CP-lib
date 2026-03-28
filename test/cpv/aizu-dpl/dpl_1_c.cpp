#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_C"

#include "../../../src/opt/knapsack/mixed/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, w;
  std::cin >> n >> w;
  knapsack_mixed<i32> kn(w);
  for (u32 i = 0; i < n; ++i) {
    i32 v;
    u32 w;
    std::cin >> v >> w;
    kn.add(w, v, 0);
  }
  std::cout << std::ranges::max(kn.result()) << '\n';
  return 0;
}
