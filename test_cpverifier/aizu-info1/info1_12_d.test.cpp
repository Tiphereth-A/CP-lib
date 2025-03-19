#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_D"

#include "../../include/ds/fenwick_2d.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, q;
  std::cin >> n >> m >> q;
  tifa_libs::ds::fenwick2d<i32> tr(n + 3, m + 3);
  for (u32 i = 0, a, b, c, d; i < q; ++i) {
    std::cin >> a >> b >> c >> d;
    tr.add(a + 1, b + 1, c + 2, d + 2, 1);
  }
  flt_ (u32, i, 1, n + 1)
    flt_ (u32, j, 1, m + 1) std::cout << tr.sum(i, j) << " \n"[j == m];
  return 0;
}
