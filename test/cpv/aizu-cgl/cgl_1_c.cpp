// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_C"

#include "../../../src/geo2d/cross/lib.hpp"
#include "../../../src/geo2d/dot/lib.hpp"
#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/geo2d/pred/is_in_middle_p/lib.hpp"

using namespace tifa_libs;
using point_t = point<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  point_t p0, p1;
  std::cin >> p0 >> p1;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    point_t p;
    std::cin >> p;
    if (is_pos(cross(p0, p1, p))) std::cout << "COUNTER_CLOCKWISE\n";
    else if (is_neg(cross(p0, p1, p))) std::cout << "CLOCKWISE\n";
    else if (is_neg(dot(p0, p1, p))) std::cout << "ONLINE_BACK\n";
    else if (is_in_middle(p0, p, p1)) std::cout << "ON_SEGMENT\n";
    else std::cout << "ONLINE_FRONT\n";
  }
  return 0;
}
