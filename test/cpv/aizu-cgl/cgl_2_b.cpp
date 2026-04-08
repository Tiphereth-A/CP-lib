// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_B"

#include "../../../src/geo2d/ds/l/lib.hpp"
#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/geo2d/pred/is_ins_ss/lib.hpp"

using namespace tifa_libs;
using point_t = point<double>;
using line_t = line<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    line_t l1, l2;
    std::cin >> l1 >> l2;
    std::cout << is_ins_SS(l1, l2) << '\n';
  }
  return 0;
}
