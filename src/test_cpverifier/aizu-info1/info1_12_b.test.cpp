#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_B"

#include "../../code/io/ios_container.hpp"
#include "../../code/util/ndvec.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::ndvec<2, i32> nv(n, m);
  std::cin >> nv;
  u32 l1, l2, r1, r2;
  std::cin >> l1 >> l2 >> r1 >> r2;
  fle_ (u32, i, l1, r1)
    fle_ (u32, j, l2, r2) std::cout << nv[i][j] << " \n"[j == r2];
  return 0;
}
