// competitive-verifier: ERROR 0.00001
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_G"

#include "../../../src/edh/discretization/lib.hpp"
#include "../../../src/geo2d/ds/c/lib.hpp"
#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/geo2d/tan/cc_ex/lib.hpp"
#include "../../../src/geo2d/tan/cc_in/lib.hpp"

using namespace tifa_libs;
using point_t = point<double>;
using circle_t = circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  circle_t c1, c2;
  std::cin >> c1 >> c2;
  auto exl = extan_CC(c1, c2), inl = intan_CC(c1, c2);
  vec<point_t> ans;
  if (exl) {
    ans.push_back(exl->first.l);
    ans.push_back(exl->second.l);
  }
  if (inl) {
    ans.push_back(inl->first.l);
    ans.push_back(inl->second.l);
  }
  ans = uniq(ans);
  for (auto& i : ans) std::cout << i << '\n';
  return 0;
}
