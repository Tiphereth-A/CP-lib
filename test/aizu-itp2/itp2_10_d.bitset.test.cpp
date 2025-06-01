#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_10_D"

#include "../../include/util/alias_others.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vec<std::bitset<64>> masks(n);
  for (auto& m : masks) {
    u32 k;
    std::cin >> k;
    flt_ (u32, i, 0, k, x) {
      std::cin >> x;
      m.set(x);
    }
  }
  u32 q;
  std::cin >> q;
  std::bitset<64> bs;
  while (q--) {
    u32 op, i;
    std::cin >> op >> i;
    switch (op) {
      case 0: std::cout << bs[i] << '\n'; break;
      case 1: bs |= masks[i]; break;
      case 2: bs &= ~masks[i]; break;
      case 3: bs ^= masks[i]; break;
      case 4: std::cout << ((bs & masks[i]) == masks[i]) << '\n'; break;
      case 5: std::cout << (bs & masks[i]).any() << '\n'; break;
      case 6: std::cout << (bs & masks[i]).none() << '\n'; break;
      case 7: std::cout << (bs & masks[i]).count() << '\n'; break;
      case 8: std::cout << (bs & masks[i]).to_ullong() << '\n'; break;
    }
  }
  return 0;
}