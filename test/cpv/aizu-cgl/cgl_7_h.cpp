// competitive-verifier: ERROR 0.000001
// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_H"

#include "../../../src/geo2d/ains/poc/lib.hpp"
#include "../../../src/geo2d/ds/po/lib.hpp"

using namespace tifa_libs;
using poly = polygon<double>;
using circ = circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  u32 n;
  double r;
  std::cin >> n >> r;
  poly pl(n);
  std::cin >> pl;
  std::cout << area_PoC(pl, {0, 0, r}) << '\n';
  return 0;
}
