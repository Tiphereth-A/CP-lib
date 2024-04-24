#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min/"

#include "../../code/ds/trie01.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 q;
  std::cin >> q;
  tifa_libs::ds::trie01<> trie(30);
  for (u32 i = 0, t, x; i < q; ++i) {
    std::cin >> t >> x;
    switch (t) {
      case 0:
        if (!trie.data[trie.find(x)].val) trie.add(x);
        break;
      case 1:
        if (trie.data[trie.find(x)].val) trie.add(x, -1);
        break;
      case 2:
        std::cout << trie.kth_element(0, x).first << "\n";
    }
  }
  return 0;
}