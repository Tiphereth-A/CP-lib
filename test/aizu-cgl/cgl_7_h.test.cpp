#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_H"
#define ERROR 0.000001

#include "../../include/geo2d/area_poc.hpp"
#include "../../include/geo2d/polygon.hpp"

using namespace tifa_libs;
using poly = geo::polygon<double>;
using circ = geo::circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  u32 n;
  double r;
  std::cin >> n >> r;
  poly pl(n);
  std::cin >> pl;
  std::cout << geo::area_PoC(pl, {0, 0, r}) << '\n';
  return 0;
}
