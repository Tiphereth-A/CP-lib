#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/9/INFO1/all/INFO1_12_A"

#include "../../include/io/ios_container.hpp"
#include "../../include/util/ndvec.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  ndvec<2, i32> nv(n, m);
  std::cin >> nv;
  u32 i, j;
  std::cin >> i >> j;
  std::cout << nv(i, j) << '\n';
  return 0;
}
