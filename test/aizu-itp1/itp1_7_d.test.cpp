#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/all/ITP1_7_D"

#include "../../include/lalg/mat.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, l;
  std::cin >> n >> m >> l;
  math::matrix<u64> a(n, m), b(m, l);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
  return 0;
}
