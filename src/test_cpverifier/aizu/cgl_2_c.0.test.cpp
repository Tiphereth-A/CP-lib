#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_C"
#define ERROR 0.00000001

#include "../../code/geo2d/ins_ll.hpp"
#include "../../code/geo2d/line.hpp"
#include "../../code/geo2d/point.hpp"

using point = tifa_libs::geo::point<double>;
using line = tifa_libs::geo::line<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(10);
  tifa_libs::u32 q;
  std::cin >> q;
  for (size_t i = 0; i < q; ++i) {
    line l1, l2;
    std::cin >> l1 >> l2;
    std::cout << tifa_libs::geo::ins_LL(l1, l2) << '\n';
  }
  return 0;
}
