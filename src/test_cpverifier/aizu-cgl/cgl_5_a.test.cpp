#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_5_A"
#define ERROR 0.000001

#include "../../code/geo2d/min_dis_ps.hpp"
#include "../../code/geo2d/point.hpp"

using point = tifa_libs::geo::point<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(10);
  u32 n;
  std::cin >> n;
  vec<point> vp(n);
  for (auto &i : vp) std::cin >> i;
  std::ranges::sort(vp);
  std::cout << tifa_libs::geo::min_dis_Ps(vp, 0, n) << '\n';
  return 0;
}
