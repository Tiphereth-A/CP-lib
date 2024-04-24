#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_C"

#include "../../code/io/ios_container.hpp"
#include "../../code/util/ndvec.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, q;
  std::cin >> n >> m >> q;
  tifa_libs::ndvec<2, i32> nv(n, m);
  for (u32 i = 0, x, y; i < q; ++i) {
    std::cin >> x >> y;
    nv[x][y] = 1 - nv[x][y];
  }
  for (u32 i = 0; i < n; ++i) std::cout << nv[i] << '\n';
  return 0;
}
