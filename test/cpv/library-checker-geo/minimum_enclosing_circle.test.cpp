#define PROBLEM "https://judge.yosupo.jp/problem/minimum_enclosing_circle"

#include "../../../src/geo2d/min_cover_c/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using point = geo::point<f64>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);

  u32 n;
  std::cin >> n;
  vec<point> vp(n);
  std::cin >> vp;
  auto vp2 = vp;
  shuffle(vp2, std::mt19937{TIME});
  auto c = geo::min_cover_C(vp2);
  for (auto&& p : vp) std::cout << (geo::relation_CP(c, p) == geo::RELCP::onborder);

  return 0;
}
