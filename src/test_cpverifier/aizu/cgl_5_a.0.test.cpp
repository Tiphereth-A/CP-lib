#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_5_A"

#include "../../code/geo2d/min_dis_ps.hpp"
#include "../../code/geo2d/point.hpp"

using point = tifa_libs::geo2d::point<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(0);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<point> vp(n);
  for (auto &i : vp) std::cin >> i;
  std::sort(vp.begin(), vp.end());
  std::cout << tifa_libs::geo2d::min_dis_Ps(vp, 0, n) << '\n';
  return 0;
}
