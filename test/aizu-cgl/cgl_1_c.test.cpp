#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_C"

#include "../../include/geo2d/cross.hpp"
#include "../../include/geo2d/dot.hpp"
#include "../../include/geo2d/point.hpp"
#include "../../include/geo2d/point_is_in_middle.hpp"

using namespace tifa_libs;
using point = geo::point<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  point p0, p1;
  std::cin >> p0 >> p1;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    point p;
    std::cin >> p;
    if (is_pos(geo::cross(p0, p1, p))) std::cout << "COUNTER_CLOCKWISE\n";
    else if (is_neg(geo::cross(p0, p1, p))) std::cout << "CLOCKWISE\n";
    else if (is_neg(geo::dot(p0, p1, p))) std::cout << "ONLINE_BACK\n";
    else if (geo::is_in_middle(p0, p, p1)) std::cout << "ON_SEGMENT\n";
    else std::cout << "ONLINE_FRONT\n";
  }
  return 0;
}
