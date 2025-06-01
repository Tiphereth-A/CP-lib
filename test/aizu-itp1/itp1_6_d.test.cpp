#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/all/ITP1_6_D"

#include "../../include/lalg/mat.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  math::matrix<u64> a(n, m), b(m, 1);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
  return 0;
}
