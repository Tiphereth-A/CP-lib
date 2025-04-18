#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_F"
#define ERROR 0.000001

#include "../../include/geo2d/circle.hpp"
#include "../../include/geo2d/point.hpp"
#include "../../include/geo2d/tan_cp.hpp"

using point = tifa_libs::geo::point<double>;
using circ = tifa_libs::geo::circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  circ c;
  point p;
  std::cin >> p >> c;
  auto [x, y] = tifa_libs::geo::tan_CP(c, p).value();
  if (x < y) std::cout << x << '\n'
                       << y << '\n';
  else std::cout << y << '\n'
                 << x << '\n';
  return 0;
}
