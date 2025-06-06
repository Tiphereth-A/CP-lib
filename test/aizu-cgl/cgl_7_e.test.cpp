#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_E"
#define ERROR 0.000001

#include "../../include/geo2d/circle.hpp"
#include "../../include/geo2d/ins_cc.hpp"

using namespace tifa_libs;
using circ = geo::circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  circ c1, c2;
  std::cin >> c1 >> c2;
  auto [x, y] = geo::ins_CC(c1, c2).value();
  if (x < y) std::cout << x << ' ' << y << '\n';
  else std::cout << y << ' ' << x << '\n';
  return 0;
}
