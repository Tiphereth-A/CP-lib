#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_D"

#include "../../include/math/youngt.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  math::Youngt yt;
  for (u32 i = 0, x; i < n; ++i) {
    std::cin >> x;
    yt.insert(x);
  }
  std::cout << yt.width() << '\n';
  return 0;
}
