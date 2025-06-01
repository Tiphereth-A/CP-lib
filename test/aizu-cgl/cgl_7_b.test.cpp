#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_B"
#define ERROR 0.000001

#include "../../include/geo2d/tcenter_i.hpp"
#include "../../include/geo2d/triangle.hpp"

using namespace tifa_libs;
using tri = geo::triangle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  tri t;
  std::cin >> t;
  std::cout << geo::center_I(t) << ' ' << geo::radius_I(t) << '\n';
  return 0;
}
