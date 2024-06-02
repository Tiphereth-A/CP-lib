#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_I"
#define ERROR 0.000001

#include "../../code/geo2d/area_cc.hpp"
#include "../../code/geo2d/circle.hpp"

using circ = tifa_libs::geo::circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  circ c1, c2;
  std::cin >> c1 >> c2;
  std::cout << tifa_libs::geo::area_CC(c1, c2) << '\n';
  return 0;
}
