#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_D"

#include "../../code/math/youngt.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::math::Youngt yt;
  for (u32 i = 0, x; i < n; ++i) {
    std::cin >> x;
    yt.insert(x);
  }
  std::cout << yt.width() << '\n';
  return 0;
}
