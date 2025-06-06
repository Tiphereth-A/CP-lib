#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_B"
#define ERROR 0.00000001

#include "../../include/geo2d/line.hpp"
#include "../../include/geo2d/point.hpp"
#include "../../include/geo2d/proj.hpp"

using namespace tifa_libs;
using point = geo::point<double>;
using line = geo::line<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(10);
  line l;
  std::cin >> l;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    point p;
    std::cin >> p;
    std::cout << geo::reflect(l, p) << '\n';
  }
  return 0;
}
