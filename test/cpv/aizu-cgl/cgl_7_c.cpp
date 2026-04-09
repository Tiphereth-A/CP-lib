// competitive-verifier: ERROR 0.000001
// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_C
#include "../../../src/geo2d/ds/t/lib.hpp"
#include "../../../src/geo2d/tcenter/o/lib.hpp"

using namespace tifa_libs;
using tri = triangle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  tri t;
  std::cin >> t;
  std::cout << center_O(t) << ' ' << radius_O(t) << '\n';
  return 0;
}
