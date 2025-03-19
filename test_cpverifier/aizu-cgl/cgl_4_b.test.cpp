#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_B"
#define ERROR 0.000001

#include "../../include/geo2d/cvh.hpp"

using cvh = tifa_libs::geo::cvh<f64>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  u32 n;
  std::cin >> n;
  cvh p(n);
  std::cin >> p;
  p.init();
  std::cout << p.diameter() << '\n';
  return 0;
}
