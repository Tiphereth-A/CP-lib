#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_10_C"

#include "../../include/ds/dbitset.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 q;
  std::cin >> q;
  tifa_libs::ds::dbitset bs(64);
  while (q--) {
    u32 op, i;
    std::cin >> op;
    if (op < 4) std::cin >> i;
    switch (op) {
      case 0: std::cout << bs[i] << '\n'; break;
      case 1: bs.set(i); break;
      case 2: bs.reset(i); break;
      case 3: bs.flip(i); break;
      case 4: std::cout << bs.all() << '\n'; break;
      case 5: std::cout << bs.any() << '\n'; break;
      case 6: std::cout << bs.none() << '\n'; break;
      case 7: std::cout << bs.count() << '\n'; break;
      case 8: std::cout << bs.to_integer<u64>() << '\n'; break;
    }
  }
  return 0;
}