#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_A"

#include "../../code/geo2d/circle.hpp"
#include "../../code/geo2d/rel_cc.hpp"

using circ = tifa_libs::geo::circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  circ c1, c2;
  std::cin >> c1 >> c2;
  switch (tifa_libs::geo::relation_CC(c1, c2)) {
    case tifa_libs::geo::lyingin_cc: std::cout << "0\n"; break;
    case tifa_libs::geo::touchin_cc: std::cout << "1\n"; break;
    case tifa_libs::geo::intersect_cc: std::cout << "2\n"; break;
    case tifa_libs::geo::touchex_cc: std::cout << "3\n"; break;
    case tifa_libs::geo::lyingout_cc: std::cout << "4\n"; break;
  }
  return 0;
}
