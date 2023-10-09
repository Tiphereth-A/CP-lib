#define PROBLEM "https://www.luogu.com.cn/problem/P6242"

#include "../../code/ds/segtree_beats.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n, m;
  std::cin >> n >> m;
  tifa_libs::vec<tifa_libs::i32> a(n);
  for (auto& x : a) std::cin >> x;
  tifa_libs::ds::segtree_beats<tifa_libs::i32, tifa_libs::i64> seg(a);
  for (size_t i = 0, opt, l, r; i < m; ++i) {
    std::cin >> opt >> l >> r;
    --l, --r;
    if (opt <= 2) {
      tifa_libs::i32 k;
      std::cin >> k;
      if (opt == 1)
        seg.add(1, 0, n - 1, l, r, k);
      else
        seg.chmin(1, 0, n - 1, l, r, k);
    } else {
      if (opt == 3)
        std::cout << seg.querys(1, 0, n - 1, l, r) << '\n';
      else if (opt == 4)
        std::cout << seg.querymax(1, 0, n - 1, l, r) << '\n';
      else
        std::cout << seg.queryhismax(1, 0, n - 1, l, r) << '\n';
    }
  }
  return 0;
}
