#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_C"

#include "../../include/geo2d/point.hpp"
#include "../../include/geo2d/polygon.hpp"
#include "../../include/geo2d/rel_pop.hpp"

using namespace tifa_libs;
using point = geo::point<double>;
using poly = geo::polygon<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(1);
  u32 n;
  std::cin >> n;
  poly pl(n);
  std::cin >> pl;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    point p;
    std::cin >> p;
    switch (geo::relation_PoP(pl, p)) {
      case geo::inside_pop: std::cout << "2\n"; break;
      case geo::outside_pop: std::cout << "0\n"; break;
      default: std::cout << "1\n";
    }
  }
  return 0;
}
