// competitive-verifier: ERROR 0.000001
// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_F"

#include "../../../src/geo2d/ds/c/lib.hpp"
#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/geo2d/tan/cp/lib.hpp"

using namespace tifa_libs;
using point_t = point<double>;
using circle_t = circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  circle_t c;
  point_t p;
  std::cin >> p >> c;
  auto [x, y] = tan_CP(c, p).value();
  if (x < y) std::cout << x << '\n'
                       << y << '\n';
  else std::cout << y << '\n'
                 << x << '\n';
  return 0;
}
