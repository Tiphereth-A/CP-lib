#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_B"

#include "../../code/geo2d/polygon.hpp"

using poly = tifa_libs::geo2d::polygon<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  poly p(n);
  std::cin >> p;
  std::cout << p.is_convex() << '\n';
  return 0;
}