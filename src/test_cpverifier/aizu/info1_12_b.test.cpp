#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_B"

#include "../../code/util/ios_container.hpp"
#include "../../code/util/ndvec.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::ndvec<2, i32> nv(n, m);
  std::cin >> nv;
  u32 l1, l2, r1, r2;
  std::cin >> l1 >> l2 >> r1 >> r2;
  for (u32 i = l1; i <= r1; ++i)
    for (u32 j = l2; j <= r2; ++j) std::cout << nv[i][j] << " \n"[j == r2];
  return 0;
}
