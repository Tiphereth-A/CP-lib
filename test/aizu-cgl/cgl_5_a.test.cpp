#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_5_A"
#define ERROR 0.000001

#include "../../include/geo2d/min_dis_ps.hpp"
#include "../../include/geo2d/point.hpp"

using namespace tifa_libs;
using point = geo::point<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(10);
  u32 n;
  std::cin >> n;
  vec<point> vp(n);
  for (auto &i : vp) std::cin >> i;
  auto [l, r] = geo::min_dis_Ps(vp);
  std::cout << geo::dist_PP(vp[l], vp[r]) << '\n';
  return 0;
}
