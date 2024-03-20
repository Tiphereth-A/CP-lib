#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_D"

#include "../../code/enum/gosper.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::gosper<>::set(n, k);
  vec<u32> _;
  for (auto i : tifa_libs::gosper<>{}) {
    std::cout << i << ":";
    for (usz j = 0; j < n; ++j)
      if ((i >> j) & 1) std::cout << ' ' << j;
    std::cout << '\n';
  }
  return 0;
}
