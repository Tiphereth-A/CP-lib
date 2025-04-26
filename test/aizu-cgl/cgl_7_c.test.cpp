#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_C"
#define ERROR 0.000001

#include "../../include/geo2d/tcenter_o.hpp"
#include "../../include/geo2d/triangle.hpp"

using tri = tifa_libs::geo::triangle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  tri t;
  std::cin >> t;
  std::cout << tifa_libs::geo::center_O(t) << ' ' << tifa_libs::geo::radius_O(t) << '\n';
  return 0;
}
