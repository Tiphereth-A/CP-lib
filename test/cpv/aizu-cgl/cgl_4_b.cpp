// competitive-verifier: ERROR 0.000001
// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_B"

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using cvh_t = cvh<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  u32 n;
  std::cin >> n;
  cvh_t p(n);
  std::cin >> p;
  p.init();
  std::cout << p.diameter() << '\n';
  return 0;
}
