#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_E"

#include "../../code/util/ndvec.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 x, y, z, n;
  std::cin >> x >> y >> z >> n;
  tifa_libs::ndvec<3, i32> nv(51, 51, 51);
  for (u32 i = 0, a, b, c; i < n; ++i) {
    std::cin >> a >> b >> c;
    nv[a][b][c] = 1;
  }
  u32 q;
  std::cin >> q;
  for (u32 i = 0, a, b, c; i < q; ++i) {
    std::cin >> a >> b >> c;
    std::cout << nv[a][b][c] << '\n';
  }
  return 0;
}
