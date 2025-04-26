#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_B"

#include "../../include/geo2d/is_ins_ss.hpp"
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
    std::cout << tifa_libs::geo::is_ins_SS(l1, l2) << '\n';
  }
  return 0;
}
