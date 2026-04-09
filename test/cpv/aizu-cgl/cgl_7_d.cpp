// competitive-verifier: ERROR 0.000001
// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_D
#include "../../../src/geo2d/ds/c/lib.hpp"
#include "../../../src/geo2d/ds/l/lib.hpp"
#include "../../../src/geo2d/ins/cl/lib.hpp"

using namespace tifa_libs;
using circle_t = circle<double>;
using line_t = line<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(12);
  circle_t c;
  std::cin >> c;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    line_t l;
    std::cin >> l;
    auto [x, y] = ins_CL(c, l).value();
    if (x < y) std::cout << x << ' ' << y << '\n';
    else std::cout << y << ' ' << x << '\n';
  }
  return 0;
}
