#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_A"

#include "../../include/geo2d/line.hpp"
#include "../../include/geo2d/point.hpp"

using point = tifa_libs::geo::point<double>;
using line = tifa_libs::geo::line<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    line l1, l2;
    std::cin >> l1 >> l2;
    if (tifa_libs::is_zero(l1.direction() * l2.direction())) std::cout << "1\n";
    else if (l1.is_parallel(l2)) std::cout << "2\n";
    else std::cout << "0\n";
  }
  return 0;
}
