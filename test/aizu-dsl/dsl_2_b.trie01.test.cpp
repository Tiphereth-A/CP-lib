#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_B"

#include "../../include/ds/trie01.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  ds::trie01 bt(21);
  for (u32 i = 0, c, x, y; i < q; ++i) {
    std::cin >> c >> x >> y;
    if (c == 0) bt.add(x, (i32)y);
    else if (c == 1) std::cout << bt.count_less(y + 1) - bt.count_less(x) << "\n";
  }
  return 0;
}
