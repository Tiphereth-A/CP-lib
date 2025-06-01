#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_A"

#include "../../include/geo2d/circle.hpp"
#include "../../include/geo2d/rel_cc.hpp"

using namespace tifa_libs;
using circ = geo::circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  circ c1, c2;
  std::cin >> c1 >> c2;
  switch (geo::relation_CC(c1, c2)) {
    case geo::lyingin_cc: std::cout << "0\n"; break;
    case geo::touchin_cc: std::cout << "1\n"; break;
    case geo::intersect_cc: std::cout << "2\n"; break;
    case geo::touchex_cc: std::cout << "3\n"; break;
    case geo::lyingout_cc: std::cout << "4\n"; break;
  }
  return 0;
}
