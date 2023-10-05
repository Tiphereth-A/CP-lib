#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H"

#include "../../code/ds/segtree0.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n, q;
  std::cin >> n >> q;
  tifa_libs::vec<int32_t> a(n);
  auto min = [](int32_t a, int32_t b) { return std::min(a, b); };
  auto max = [](int32_t a, int32_t b) { return std::max(a, b); };
  tifa_libs::ds::segtree0<int32_t, decltype(min)> segt(a);
  for (size_t i = 1; i <= q; ++i) {
    size_t opt, l, r;
    std::cin >> opt >> l >> r;
    if (opt == 0) {
      int32_t x;
      std::cin >> x;
      segt.add(1, 0, n - 1, l, r, x);
    } else {
      std::cout << segt.querym(1, 0, n - 1, l, r, min) << '\n';
      // std::cout << std::endl;
    }
  }
  return 0;
}
