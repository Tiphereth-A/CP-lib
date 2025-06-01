#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_D"
#define ERROR 0.00000001

#include "../../include/geo2d/dist_ss.hpp"
#include "../../include/geo2d/line.hpp"
#include "../../include/geo2d/point.hpp"

using namespace tifa_libs;
using point = geo::point<double>;
using line = geo::line<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(10);
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    line l1, l2;
    std::cin >> l1 >> l2;
    std::cout << geo::dist_SS(l1, l2) << '\n';
  }
  return 0;
}
