#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_C"

#include "../../code/geo2d/point.hpp"
#include "../../code/geo2d/polygon.hpp"
#include "../../code/geo2d/rel_pop.hpp"

using point = tifa_libs::geo::point<double>;
using poly = tifa_libs::geo::polygon<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(1);
  u32 n;
  std::cin >> n;
  poly pl(n);
  std::cin >> pl;
  u32 q;
  std::cin >> q;
  for (usz i = 0; i < q; ++i) {
    point p;
    std::cin >> p;
    switch (tifa_libs::geo::relation_PoP(pl, p)) {
      case tifa_libs::geo::inside_pop: std::cout << "2\n"; break;
      case tifa_libs::geo::outside_pop: std::cout << "0\n"; break;
      default: std::cout << "1\n";
    }
  }
  return 0;
}
