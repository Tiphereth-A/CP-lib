#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_D"
#define ERROR 0.00000001

#include "../../code/geo2d/dist_ss.hpp"
#include "../../code/geo2d/line.hpp"
#include "../../code/geo2d/point.hpp"

using point = tifa_libs::geo::point<double>;
using line = tifa_libs::geo::line<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(10);
  u32 q;
  std::cin >> q;
  for (usz i = 0; i < q; ++i) {
    line l1, l2;
    std::cin >> l1 >> l2;
    std::cout << tifa_libs::geo::dist_SS(l1, l2) << '\n';
  }
  return 0;
}
