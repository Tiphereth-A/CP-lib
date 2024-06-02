#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_D"

#include "../../code/enum/gosper.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::gosper<>::set(n, k);
  vecu _;
  for (auto i : tifa_libs::gosper<>{}) {
    std::cout << i << ":";
    flt_ (u32, j, 0, n)
      if ((i >> j) & 1) std::cout << ' ' << j;
    std::cout << '\n';
  }
  return 0;
}
