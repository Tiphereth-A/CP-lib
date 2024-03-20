#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_C"

#include "../../code/enum/enum_subset.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  u32 b = 0;
  for (u32 i = 0, x; i < k; ++i) {
    std::cin >> x;
    b |= 1 << x;
  }
  tifa_libs::enum_subset<>::set(b);
  vec<u32> _;
  for (auto i : tifa_libs::enum_subset<>{}) _.push_back(i);
  _.push_back(0);
  std::reverse(_.begin(), _.end());
  for (auto i : _) {
    std::cout << i << ":";
    for (usz j = 0; j < n; ++j)
      if ((i >> j) & 1) std::cout << ' ' << j;
    std::cout << '\n';
  }
  return 0;
}
