#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_B"

#include "../../include/geo2d/polygon.hpp"

using poly = tifa_libs::geo::polygon<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  poly p(n);
  std::cin >> p;
  std::cout << p.is_convex() << '\n';
  return 0;
}
