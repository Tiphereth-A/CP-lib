#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_A"

#include "../../code/util/ios_container.hpp"
#include "../../code/util/ndvec.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::ndvec<2, i32> nv(n, m);
  std::cin >> nv;
  u32 i, j;
  std::cin >> i >> j;
  std::cout << nv[i][j] << '\n';
  return 0;
}
