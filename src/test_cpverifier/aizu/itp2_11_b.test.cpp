#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_B"

#include "../../code/enum/enum_supset.hpp"

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
  tifa_libs::enum_supset<>::set(b, n);
  for (auto i : tifa_libs::enum_supset<>{}) {
    std::cout << i << ":";
    for (usz j = 0; j < n; ++j)
      if ((i >> j) & 1) std::cout << ' ' << j;
    std::cout << '\n';
  }
  return 0;
}
