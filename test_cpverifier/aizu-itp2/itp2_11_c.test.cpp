#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_C"

#include "../../include/enum/enum_subset.hpp"
#include "../../include/util/alias_others.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  u32 b = 0;
  for (u32 i = 0, x; i < k; ++i) {
    std::cin >> x;
    b |= 1 << x;
  }
  tifa_libs::enum_subset<>::set(b);
  vecu _;
  for (auto i : tifa_libs::enum_subset<>{}) _.push_back(i);
  _.push_back(0);
  std::ranges::reverse(_);
  for (auto i : _) {
    std::cout << i << ":";
    flt_ (u32, j, 0, n)
      if ((i >> j) & 1) std::cout << ' ' << j;
    std::cout << '\n';
  }
  return 0;
}
