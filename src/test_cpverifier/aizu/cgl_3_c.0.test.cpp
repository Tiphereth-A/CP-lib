#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_C"

#include "../../code/geo2d/point.hpp"
#include "../../code/geo2d/polygon.hpp"
#include "../../code/geo2d/rel_pop.hpp"

using point = tifa_libs::geo2d::point<double>;
using poly = tifa_libs::geo2d::polygon<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(1);
  tifa_libs::u32 n;
  std::cin >> n;
  poly pl(n);
  std::cin >> pl;
  tifa_libs::u32 q;
  std::cin >> q;
  for (size_t i = 0; i < q; ++i) {
    point p;
    std::cin >> p;
    switch (tifa_libs::geo2d::relation_PoP(pl, p)) {
      case tifa_libs::geo2d::inside_pop: std::cout << "2\n"; break;
      case tifa_libs::geo2d::outside_pop: std::cout << "0\n"; break;
      default: std::cout << "1\n";
    }
  }
  return 0;
}
