#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_D"
#define ERROR 0.000001

#include "../../code/geo2d/circle.hpp"
#include "../../code/geo2d/ins_cl.hpp"
#include "../../code/geo2d/line.hpp"

using circ = tifa_libs::geo::circle<double>;
using line = tifa_libs::geo::line<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);
  circ c;
  std::cin >> c;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    line l;
    std::cin >> l;
    auto [x, y] = tifa_libs::geo::ins_CL(c, l).value();
    if (x < y) std::cout << x << ' ' << y << '\n';
    else std::cout << y << ' ' << x << '\n';
  }
  return 0;
}
