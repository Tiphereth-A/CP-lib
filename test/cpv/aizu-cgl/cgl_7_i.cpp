// competitive-verifier: ERROR 0.000001
// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_I"

#include "../../../src/geo2d/ains/cc/lib.hpp"
#include "../../../src/geo2d/ds/c/lib.hpp"

using namespace tifa_libs;
using circ = circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  circ c1, c2;
  std::cin >> c1 >> c2;
  std::cout << area_CC(c1, c2) << '\n';
  return 0;
}
