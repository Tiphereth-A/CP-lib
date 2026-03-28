// competitive-verifier: ERROR 0.000001
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_B"

#include "../../../src/geo2d/ds/t/lib.hpp"
#include "../../../src/geo2d/tcenter/i/lib.hpp"

using namespace tifa_libs;
using tri = triangle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  tri t;
  std::cin >> t;
  std::cout << center_I(t) << ' ' << radius_I(t) << '\n';
  return 0;
}
