// competitive-verifier: ERROR 0.000001
// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_5_A"

#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/geo2d/min_dis_ps/lib.hpp"

using namespace tifa_libs;
using point_t = point<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(10);
  u32 n;
  std::cin >> n;
  vec<point_t> vp(n);
  for (auto& i : vp) std::cin >> i;
  auto [l, r] = min_dis_Ps(vp);
  std::cout << dist_PP(vp[l], vp[r]) << '\n';
  return 0;
}
