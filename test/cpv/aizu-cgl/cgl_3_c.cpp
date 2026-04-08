// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_C"

#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/geo2d/ds/po/lib.hpp"
#include "../../../src/geo2d/rel/pop/lib.hpp"

using namespace tifa_libs;
using point_t = point<double>;
using polygon_t = polygon<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(1);
  u32 n;
  std::cin >> n;
  polygon_t pl(n);
  std::cin >> pl;
  u32 q;
  std::cin >> q;
  flt_ (u32, i, 0, q) {
    point_t p;
    std::cin >> p;
    switch (relation_PoP(pl, p)) {
      case RELPoP::inside: std::cout << "2\n"; break;
      case RELPoP::outside: std::cout << "0\n"; break;
      default: std::cout << "1\n";
    }
  }
  return 0;
}
