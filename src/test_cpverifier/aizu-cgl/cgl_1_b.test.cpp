#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_B"
#define ERROR 0.00000001

#include "../../code/geo2d/line.hpp"
#include "../../code/geo2d/point.hpp"
#include "../../code/geo2d/proj.hpp"

using point = tifa_libs::geo::point<double>;
using line = tifa_libs::geo::line<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(10);
  line l;
  std::cin >> l;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    point p;
    std::cin >> p;
    std::cout << tifa_libs::geo::reflect(l, p) << '\n';
  }
  return 0;
}
