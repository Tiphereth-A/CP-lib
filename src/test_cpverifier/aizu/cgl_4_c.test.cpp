#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_C"
#define ERROR 0.00001

#include "../../code/geo2d/cvh.hpp"
#include "../../code/geo2d/line.hpp"

using cvh = tifa_libs::geo::cvh<double>;
using line = tifa_libs::geo::line<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(8);
  u32 n;
  std::cin >> n;
  cvh p(n);
  std::cin >> p;
  p.init();
  u32 q;
  std::cin >> q;
  for (u32 i = 0; i < q; ++i) {
    line l;
    std::cin >> l;
    auto _ = p;
    std::cout << _.do_ins_CVHhP(l).area() << '\n';
  }
  return 0;
}
