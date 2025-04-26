#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_C"

#include "../../include/util/ndvec.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, q;
  std::cin >> n >> m >> q;
  tifa_libs::ndvec<2, i32> nv(n, m);
  for (u32 i = 0, x, y; i < q; ++i) {
    std::cin >> x >> y;
    nv(x, y) = 1 - nv(x, y);
  }
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, m) std::cout << nv(i, j) << " \n"[j + 1 == m];
  return 0;
}
