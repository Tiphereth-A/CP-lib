// competitive-verifier: ERROR 0.00000001
// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_A
#include "../../../src/geo2d/ds/l/lib.hpp"
#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/geo2d/proj/lib.hpp"

using namespace tifa_libs;
using point_t = point<double>;
using line_t = line<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(10);
  line_t l;
  std::cin >> l;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    point_t p;
    std::cin >> p;
    std::cout << proj(l, p) << '\n';
  }
  return 0;
}
