#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_A"

#include "../../code/geo2d/line.hpp"
#include "../../code/geo2d/point.hpp"
#include "../../code/geo2d/proj.hpp"

using point = tifa_libs::geo2d::point<double>;
using line = tifa_libs::geo2d::line<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  line l;
  std::cin >> l;
  tifa_libs::u32 q;
  std::cin >> q;
  std::cout << std::fixed << std::setprecision(10);
  for (size_t i = 0; i < q; ++i) {
    point p;
    std::cin >> p;
    std::cout << tifa_libs::geo2d::proj(l, p) << '\n';
  }
  return 0;
}
