// competitive-verifier: ERROR 0.00001
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_C"

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/geo2d/ds/l/lib.hpp"

using namespace tifa_libs;
using cvh_t = cvh<double>;
using line_t = line<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(8);
  u32 n;
  std::cin >> n;
  cvh_t p(n);
  std::cin >> p;
  p.init();
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    line_t l;
    std::cin >> l;
    auto _ = p;
    std::cout << _.do_ins_CVHhP(l).area() << '\n';
  }
  return 0;
}
