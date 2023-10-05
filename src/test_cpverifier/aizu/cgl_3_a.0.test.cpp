#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_A"

#include "../../code/geo2d/polygon.hpp"

using poly = tifa_libs::geo::polygon<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(1);
  tifa_libs::u32 n;
  std::cin >> n;
  poly p(n);
  std::cin >> p;
  std::cout << p.area() << '\n';
  return 0;
}
