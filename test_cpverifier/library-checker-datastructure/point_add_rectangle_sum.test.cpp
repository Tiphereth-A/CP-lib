#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../../include/ds/kdtree.hpp"

i64 op(i64 x, i64 y) { return x + y; }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ds::KDtree<i64, op> kdt(3000);
  using point_t = decltype(kdt)::point;
  point_t p1, p2;
  i64 w;
  flt_ (u32, i, 0, n) {
    std::cin >> p1[0] >> p1[1] >> w;
    kdt.insert(p1, w);
  }
  flt_ (u32, i, 0, q, opt) {
    std::cin >> opt >> p1[0] >> p1[1];
    if (!opt) {
      std::cin >> w;
      kdt.insert(p1, w);
    } else {
      std::cin >> p2[0] >> p2[1];
      --p2[0], --p2[1];
      std::cout << kdt.query(p1, p2) << '\n';
    }
  }
  return 0;
}
